#include "nst_sysinc.h"
#include <vector>
#include <unordered_map>
#include <functional>
#include "nst_hashmap.h"
#include "nst_filereader.h"
#include "nst_string.h"
#include "nst_datafile.h"
#include "nst_mapdata.h"
#include "nst_animations.h"


std::vector<MapData::TempAni> MapData::GameMapData::ParseAnimations(FileReader& fr)
{
	using MapData::TempAni;

	std::vector< TempAni> ret;
	TempAni curr_ani;
	String curr_trigger;
	String curr_trigger_arg;
	String curr_object_name;

	char b[FILEREADER_MAX_LINE_LENGTH];
	for (fr.ReadLine(b); fr.ReadLine(b) && String(b).Trim().SubStr(0, 1) != "{/"; )
	{
		String buf = String(b).Trim();
		char* col = strchr(buf, ':');

		if (buf[0] == '#' || buf == "")
			continue;

		if (col)
		{
			*col = '\0';

         char* par_open = strchr(buf, '(');
			char* par_close = strchr(buf, ')');

			if(!(par_open && par_close))
			{
				printf("Missing arguments or parenthese in animation file for object '%s'. '%s'\n", curr_object_name.CStr(), buf.CStr());
				exit(1);
			}
			*par_close = '\0';
			*par_open = '\0';

			curr_trigger_arg = ++par_open;
			curr_trigger = buf; //get everything before the colon and save it as the trigger
			//printf("found a trigger '%s' with args '%s'\n", curr_trigger.CStr(), curr_trigger_arg.CStr());
			continue;
		}
		else if (buf.SubStr(0, 1) == "[/")
		{
			continue;
		}
		else if (buf[0] == '[' && buf[1] != '/') //means we have a new object header
		{
			curr_object_name = buf.SubStr(1, buf.Length() - 2);
		}
		else
		{
			char* c;
			for (c = buf; *c; ++c)
			{
				if (*c <= 32)
				{
					*c = 0; //mark the space with a 0
					break;
				}
			}
			curr_ani.trigger = curr_trigger;
			curr_ani.trigger_args = curr_trigger_arg;
			curr_ani.action = buf;
			curr_ani.action_args = ++c;
			curr_ani.object = curr_object_name;
			ret.push_back(curr_ani);
		}
	}
	return ret;
}


void MapData::GameMapData::GetAnimations()
{
   TriggerLookup triggers;
	ActionLookup actions;
	triggers =     {
							{"forever", [](String args){return new Animations::TriggerForever(args);}},
							{"interval", [](String args){return new Animations::TriggerInterval(args);}}
						}; 

	actions =      {
							{"move", [](String args){return new Animations::ActionMove(args);}}
						};

	FileReader fr;
	int line = 0;
	String filename = map_name + "_ani.nst";
	
	std::vector<TempAni> parsed_animations;

	if (!fr.Open(filename))
	{
		throw DataFile::ErrOpenFile(filename);
	}

	char buffer[FILEREADER_MAX_LINE_LENGTH];
	while (fr.ReadLine(buffer))
	{
		line++;
		String b = String(buffer).Trim();
		if (b == "")
			continue;
		if (line == 1 && b[0] == '_' && b[b.Length() - 1] == '_')
		{
			if (b.SubStr(1, b.Length() - 2) != map_name)
				throw WrongAniFile(filename);
		}
		else if (b == "{animations}")
		{
			parsed_animations = ParseAnimations(fr);
		}
	}

	//iterate through all animations, see if the objects they belong to exists, then construct animation objects
	
	for (std::vector<TempAni>::iterator tani = parsed_animations.begin(); tani != parsed_animations.end(); ++tani)
	{
		if (!object_lookup[tani->object]) //object doesnt exist in map file
		{
			printf("Object '%s' found in animation file, but not in main map file!\n", tani->object.CStr());
			continue;
		}
		else
		{
			if (triggers.find(tani->trigger.CStr()) == triggers.end())
			{
				printf("Could not find trigger '%s'. Skipping.\n", tani->trigger.CStr());
				continue;
			}
			if (actions.find(tani->action.CStr()) == actions.end())
			{
				printf("Could not find action '%s'. Skipping.\n", tani->action.CStr());
				continue;
			}
			//now find the object to link the action to
			MapObject* parent_object;
			for (std::vector<MapObject>::iterator o = objects.begin(); o != objects.end(); ++o)
			{
				if (tani->object == o->name)
					parent_object = &(*o);
			}
			AnimationTrigger* trigger = triggers[tani->trigger.CStr()](tani->trigger_args);
			AnimationAction* action = actions[tani->action.CStr()](tani->action_args);
			Animation ani(	*trigger,
								*action,
								parent_object);
			animations.push_back(ani);
		}
	}
}
