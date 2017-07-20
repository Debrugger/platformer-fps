#include "nst_sysinc.h"
#include <vector>
#include "nst_filereader.h"
#include "nst_string.h"
#include "nst_hashmap.h"
#include "nst_datafile.h"

int* DataFile::ConfigValue::GetIntArr() const
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
				throw BadValue(val);
			com++;
		}
	}
	return ret;
}

double* DataFile::ConfigValue::GetDoubleArr() const
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
				throw BadValue(val);
			com++;
		}
	}
	return ret;
}


std::vector<DataFile::ConfigBlock*> DataFile::ParseNextSection(FileReader& fr)
{
	std::vector<ConfigBlock*> blocks;

	//HASHMAP cant be passed by value so we need to make a new instance everytime
	//TODO delete it after use, maybe return vector of pointers instead of value
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
			blocks.push_back(new_block);
			new_block = new ConfigBlock;
		}
		else if (buf[0] == '[')
		{
			(*new_block)["name"] = buf.SubStr(1, buf.Length() - 2);
		}

		if (eq)
		{
			*eq = 0;
			String new_value = eq + 1;
			new_value = new_value.Trim();
			(*new_block)[buf].Set(new_value);
		}

	}
	return blocks;
}
