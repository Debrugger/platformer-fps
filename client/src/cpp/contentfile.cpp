#include "sysinc.h"
#include "filereader.h"
#include "hashmap.h"
#include "contentfile.h"

char* Trim(char* input)
{
	char* c;
	for (c = input; strlen(c) < FILEREADER_MAX_LINE_LENGTH; c++)
	{
		printf("in for loop\n");
		if (*c <= 32)
			continue;
		else break;
	}
	char* e = input + strlen(input) - 1;
	for (e; *e <= 32 && e >= input; e--);
	*(e+1) = 0;
	return c;
}

class ContentFile::ConfigValue
{
	union
	{
		char* name;
		int num_int;
		double num_double;
		int arr_int[3];
		double arr_double[3];
	} value;
	enum Type { t_string, t_int, t_double, t_intarr, t_doublearr };
	Type type;
	//define operator= so it recognizesthe type
};

Hashmap<ContentFile::ConfigValue> ContentFile::ParseFile(char* filename)
{
	Hashmap<ConfigValue> ret;
	FileReader fr;
	char buffer[FILEREADER_MAX_LINE_LENGTH];
	int line;
	char* eq;

	if (!fr.Open(filename))
		throw ErrOpenFile();
	while (fr.ReadLine(buffer))
	{
		line++;
		if (!(eq = strchr(buffer, '=')) || (buffer[0] == '#'))
			continue;
		*eq = 0;
		char* trimmed_key = Trim(buffer);
		if (!*trimmed_key) continue;
		ret[trimmed_key] = Trim(eq+1);
	}
	return ret;
}
