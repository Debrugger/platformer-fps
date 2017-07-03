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

Hashmap<ContentFile::ConfigValue> ContentFile::ParseNextBlock(FileReader& fr)
{
	Hashmap<ConfigValue> ret;
	char buffer[FILEREADER_MAX_LINE_LENGTH];
	char* eq;

	while (fr.ReadLine(buffer) && String(buffer).Trim()[0] != '[' && String(buffer).Trim()[0] == '{')
	{
		if (!(eq = strchr(buffer, '=')) || (buffer[0] == '#'))
			continue;
		*eq = 0;
		String key = buffer;
		String trimmed_key = key.Trim();
		if (trimmed_key == "") continue;
		String r = eq + 1;
		//TODO this should work w/ [] operator
		char* rk = trimmed_key.CStr();
		ret.Fetch(rk)->Set(r.Trim());
	}
	return ret;
}

std::vector<Hashmap<ContentFile::ConfigValue> > ContentFile::ParseNextSection(FileReader& fr)
{
	char buffer[FILEREADER_MAX_LINE_LENGTH];
	std::vector<Hashmap<ContentFile::ConfigValue> > ret;

	fr.ReadLine(buffer);
	while (fr.ReadLine(buffer))
	{
		printf("in ParseNextSection() with buffer '%s'\n", buffer);
		String buf = String(buffer).Trim();
		if (buf[0] == '{') //means we have reached next section
		{
			printf("found next section, leaving ParseNextSection()\n");
			return ret;
		}

		Hashmap<ContentFile::ConfigValue> t = ContentFile::ParseNextBlock(fr);
		ret.push_back(t);
	}
	return ret;
}




ContentFile::GameMapData ContentFile::BuildMapData(char* filename)
{
	FileReader fr;
	char buffer[FILEREADER_MAX_LINE_LENGTH];
	String map_name = "Map with no name";
	GameMapData ret;

	std::vector< Hashmap< ContentFile::ConfigValue > > map_spawnpoints;
	std::vector< Hashmap< ContentFile::ConfigValue > > map_objects;

	if (!fr.Open(filename))
		throw ContentFile::ErrOpenFile();

	while (fr.ReadLine(buffer))
	{		
		String b = String(buffer).Trim();
		if (b[0] == '<')
		{
			map_name = b.SubStr(1, b.Length() - 2);
			printf("encountered map name '%s'\n", map_name.CStr());
		}
		else if (b == "{objects}")
		{
			printf("encountered object header\n");
			map_objects = ParseNextSection(fr);
		}
		else if (b == "{spawnpoints}")
		{
			printf("encountered spawnpoint header\n");
			map_spawnpoints = ParseNextSection(fr);
		}
	}

	fr.Close();
	GameMapObject o;
	for (auto mo : map_objects)
	{
		o.obj_file_name = mo["model"].GetString();
		o.texture_diff = mo["tex_diff"].GetString();
		double* t = mo["translation"].GetDoubleArr();
		for (int i = 0; i < 3; i++)
		{
			o.translation[i] = t[i];
			printf("Object coordinate %.2f\n", o.translation[i]);
		}
		double* r = mo["rotation"].GetDoubleArr();
		for (int i = 0; i < 3; i++)
		{
			o.rotation[i] = r[i];
			printf("Object rotation %.2f\n", o.rotation[i]);
		}
		double* s = mo["scale"].GetDoubleArr();
		for (int i = 0; i < 3; i++)
		{
			o.scale[i] = s[i];
			printf("Object scale %.2f\n", o.scale[i]);
		}
		ret.objects.push_back(o);
	}

	Point p;
	for (auto ms : map_spawnpoints)
	{
		double* c = ms["coords"].GetDoubleArr();
		for (int i = 0; i < 3; i++)
		{
			p.coords[i] = c[i];
			printf("spawnpoint coord: %.2f\n", p.coords[i]);
		}
		ret.spawnpoints.push_back(p);
	}

	return ret;
}
