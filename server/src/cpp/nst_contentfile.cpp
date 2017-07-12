#include "nst_sysinc.h"
#include <vector>
#include "nst_filereader.h"
#include "nst_string.h"
#include "nst_hashmap.h"
#include "nst_contentfile.h"

//HOW TO SYNC MAP BETWEEN SERVER AND CLIENT??

typedef Hashmap< ContentFile::ConfigValue > ConfigBlock;

int* ContentFile::ConfigValue::GetIntArr()
{
	//terrible needs VECTOR class
	int* ret = new int[3];
	char* com = val;
	for (int i = 0; i < 3; i++)
	{
		ret[i] = atoi(com);
		if (i < 2)
		{
			com = strchr(com, ',');
			if (!com)
				throw BadValue();
			com++;
		}
	}
	return ret;
}

double* ContentFile::ConfigValue::GetDoubleArr()
{
	//terrible needs VECTOR class
	double* ret = new double[3];
	char* com = val;
	for (int i = 0; i < 3; i++)
	{
		ret[i] = atof(com);
		if (i < 2)
		{
			com = strchr(com, ',');
			if (!com)
				throw BadValue();
			com++;
		}
	}
	return ret;
}


std::vector<ConfigBlock> ContentFile::ParseNextSection(FileReader& fr)
{
	std::vector<ConfigBlock> blocks;

	//THIS SHOULD NOT BE A POINTER BUT WE CANT CLEAR THE HASHMAP YET
	ConfigBlock* new_block = new ConfigBlock;

	char b[FILEREADER_MAX_LINE_LENGTH];
	for (fr.ReadLine(b); fr.ReadLine(b) && String(b).Trim().SubStr(0, 1) != "{/"; )
	{
		String buf = String(b).Trim();

		char* eq = strchr(buf, '=');

		bool skip_line = (buf[0] != '[') && (!eq || (buf[0] == '#' || buf == ""));
		if (skip_line)
			continue;

		if (buf.SubStr(0, 1) == "[/")
		{
			std::cout << "pushing back new block with name " << new_block->operator[]("name").GetString() << "\n";
			blocks.push_back(*new_block);
			delete new_block; //should just be clear the hashmap
			new_block = new ConfigBlock;
		}
		else if (buf[0] == '[')
		{
			new_block->operator[]("name") = buf.SubStr(1, buf.Length() - 2);
		}

		if (eq)
		{
			*eq = 0;
			String new_value = eq + 1;
			new_value = new_value.Trim();
			new_block->operator[](buf).Set(new_value);
		}

	}
	return blocks;
}

ContentFile::GameMapData ContentFile::BuildMapData(const String filename)
{
	FileReader fr;
	char buffer[FILEREADER_MAX_LINE_LENGTH];
	String map_name;
	GameMapData ret;

	std::vector<ConfigBlock> map_spawnpoints;
	std::vector<ConfigBlock> map_objects;

	if (!fr.Open(filename))
		throw ContentFile::ErrOpenFile();

	while (fr.ReadLine(buffer))
	{		
		String b = String(buffer).Trim();
		if (b[0] == '<' && b[b.Length() - 1] == '>')
		{
			map_name = b.SubStr(1, b.Length() - 2);
		}
		else if (b == "{objects}")
		{
			map_objects = ParseNextSection(fr);
			printf("name 4: %s\n", map_objects[1]["name"].GetString().CStr());
		}
		else if (b == "{spawnpoints}")
		{
			map_spawnpoints = ParseNextSection(fr);
		}
	}

	fr.Close();
	GameMapObject o;
	Hashmap<bool> map_object_lookup; //to check if the obect exists when parsing the action file

	for (int i = 0; i < map_objects.size(); i++)
	{
		ConfigBlock& mo = map_objects[i];
		std::cout << "pushing back new object with name " << mo["name"].GetString() << "\n";
		o.name = mo["name"].GetString();

		map_object_lookup[o.name] = true;

		o.obj_file_name = mo["model"].GetString();
		o.texture_diff = mo["tex_diff"].GetString();
		double* t = mo["translation"].GetDoubleArr();
		double* r = mo["rotation"].GetDoubleArr();
		double* s = mo["scale"].GetDoubleArr();
		for (int i = 0; i < 3; i++)
		{
			o.translation[i] = t[i];
			o.rotation[i] = r[i];
			o.scale[i] = s[i];
		}
		ret.objects.push_back(o);
	}

	Point p;
	for (auto ms : map_spawnpoints)
	{
		double* c = ms["translation"].GetDoubleArr();
		for (int i = 0; i < 3; i++)
		{
			p.coords[i] = c[i];
		}
		ret.spawnpoints.push_back(p);
	}
	ret.name = map_name;

	//parse action file, then associate each action with its object

	return ret;
}
