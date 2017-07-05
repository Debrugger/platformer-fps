#include "nst_sysinc.h"
#include <vector>
#include "nst_filereader.h"
#include "nst_string.h"
#include "nst_hashmap.h"
#include "nst_contentfile.h"

//THIS ACTUALLY HAS TO BE IN THE SERVER BUT HOW TO SYNC MAP BETWEEN SERVER AND CLIENT??

int* ContentFile::ConfigValue::GetIntArr()
{
	//terrible needs VECTOR class
	int* ret = new int[3];
	char* com = val.CStr();
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
	char* com = val.CStr();
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


std::vector< Hashmap< ContentFile::ConfigValue > > ContentFile::ParseNextSection(FileReader& fr)
{
	//TODO doesnt work doesnt print out the final part in for loop probably something wrong with hashmap usage
	std::vector< Hashmap< ContentFile::ConfigValue > > blocks;

	Hashmap<ContentFile::ConfigValue> new_block;

	char b[FILEREADER_MAX_LINE_LENGTH];
	for (fr.ReadLine(b); fr.ReadLine(b) && String(b).Trim().SubStr(0, 1) != "{/"; )
	{
		String buf = String(b).Trim();

		char* eq = strchr(buf.CStr(), '=');

		bool skip_line = (buf[0] != '[') && (!eq || (buf[0] == '#' || buf == ""));
		if (skip_line)
			continue;

		if (buf.SubStr(0, 1) == "[/")
		{
			blocks.push_back(new_block);
		}
		else if (buf[0] == '[')
		{
			new_block["name"] = buf.SubStr(1, buf.Length() - 2);
		}

		if (eq)
		{
			*eq = 0;
			String new_value = eq + 1;
			new_block[buf.CStr()].Set(new_value.Trim());
		}

	}
	return blocks;
}

ContentFile::GameMapData ContentFile::BuildMapData(const String filename)
{
	FileReader fr;
	char buffer[FILEREADER_MAX_LINE_LENGTH];
	String map_name = "Map with no name";
	GameMapData ret;

	std::vector< Hashmap< ContentFile::ConfigValue > > map_spawnpoints;
	std::vector< Hashmap< ContentFile::ConfigValue > > map_objects;

	if (!fr.Open(filename.CStr()))
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
		}
		else if (b == "{spawnpoints}")
		{
			map_spawnpoints = ParseNextSection(fr);
		}
	}

	fr.Close();
	GameMapObject o;
	for (auto mo : map_objects)
	{
		o.name = mo["name"].GetString();
		o.obj_file_name = mo["model"].GetString();
		o.texture_diff = mo["tex_diff"].GetString();
		double* t = mo["translation"].GetDoubleArr();
		for (int i = 0; i < 3; i++)
		{
			o.translation[i] = t[i];
		}
		double* r = mo["rotation"].GetDoubleArr();
		for (int i = 0; i < 3; i++)
		{
			o.rotation[i] = r[i];
		}
		double* s = mo["scale"].GetDoubleArr();
		for (int i = 0; i < 3; i++)
		{
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

	return ret;
}
