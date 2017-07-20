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

MapData::MapObject::MapObject(String n, String ofn, String tex_d, std::vector<double> t, std::vector<double> r, std::vector<double> s)
{
	name = n;
	obj_file_name = ofn;
	texture_diff = tex_d;
	translation = t;
	translation.resize(3);
	rotation = r;
	rotation.resize(3);
	scale = s;
	scale.resize(3);
}

MapData::MapObject::~MapObject()
{
}

MapData::GameMapData::GameMapData(const String map_name)
{
	triggers["forever"]      = [](String args){return new Animations::TriggerForever(args);};
	triggers["interval"]     = [](String args){return new Animations::TriggerInterval(args);};

	actions["move"]          = [](String args){return new Animations::ActionMove(args);};


	try
	{
		BuildMapData(map_name);
		GetAnimations();
	}
	catch(DataFile::ErrOpenFile& e)
	{
		printf("Could not open open file '%s'. Exiting.\n", e.file.CStr());
	}
	catch(WrongAniFile& e)
	{
		printf("Animation file '%s' does not match the map it is named after.\n", e.file.CStr());
	}
}

void MapData::GameMapData::BuildMapData(const String _map_name)
{
	map_name = _map_name;
	FileReader fr;

	ConfigBlockList map_spawnpoints;
	ConfigBlockList map_objects;

	String filename = map_name + ".nst";
	if (!fr.Open(filename))
		throw DataFile::ErrOpenFile(filename);
	char buffer[FILEREADER_MAX_LINE_LENGTH];

	while (fr.ReadLine(buffer))
	{		
		String b = String(buffer).Trim();
		if (b[0] == '<' && b[b.Length() - 1] == '>')
		{
			map_name = b.SubStr(1, b.Length() - 2);
		}
		else if (b == "{objects}")
		{
			map_objects = DataFile::ParseNextSection(fr);
		}
		else if (b == "{spawnpoints}")
		{
			map_spawnpoints = DataFile::ParseNextSection(fr);
		}
	}

	fr.Close();

	ExtractMapData(map_objects, map_spawnpoints, object_lookup);
}

void MapData::GameMapData::ExtractMapData(ConfigBlockList& object_blocks, ConfigBlockList& spawn_blocks, Hashmap<bool>& object_lookup)
{
	for (ConfigBlockList::iterator i = object_blocks.begin(); i != object_blocks.end(); ++i)
	{
		MapObject o;
		ConfigBlock& mo = **i;

		String name = mo["name"].GetString();
		String obj_file_name = mo["model"].GetString();
		String texture_diff = mo["tex_diff"].GetString();
		try
		{
			double* _t = mo["translation"].GetDoubleArr();
			double* _r = mo["rotation"].GetDoubleArr();
			double* _s = mo["scale"].GetDoubleArr();
			std::vector<double> t(_t, _t + 3);
			std::vector<double> r(_r, _r + 3);
			std::vector<double> s(_s, _s + 3);
			MapObject o(name, obj_file_name, texture_diff, t, r, s);
			objects.push_back(o);
			object_lookup[o.Name().CStr()] = true;
			delete *i;
		}
		catch (DataFile::BadValue& e)
		{
			printf("Error in map file, skipping object '%s'\n", o.Name().CStr());
			continue;
		}
	}

	Point p;
	for (ConfigBlockList::iterator i = spawn_blocks.begin(); i != spawn_blocks.end(); ++i)
	{
		ConfigBlock& ms = **i;
		double* c = ms["translation"].GetDoubleArr();
		for (int i = 0; i < 3; i++)
		{
			p.coords[i] = c[i];
		}
		spawnpoints.push_back(p);
	}
}

MapData::AnimationAction::~AnimationAction()
{
}

MapData::AnimationTrigger::~AnimationTrigger()
{
}
