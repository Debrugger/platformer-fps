#ifdef NOCOMPLIETHIS
#include "sysinc.h"
#include "filereader.h"
#include "character_file.h"

CharacterFile::TempCharacter::TempCharacter()
{
	max_health = 100;
	mvmt_speed = 1.0;
	jump_height = 1.0;
	armor = 0.0;
	jetpack = false;
}

void CharacterFile::Load(char* filename)
{
	FileReader fr;
	char buffer[FILEREADER_MAX_LINE_LENGTH];
	int line = 0;
	char* eq;
	TempCharacter c;

	try
	{
		if (!fr.Open(filename)) throw ErrorOpeningFile();
		while (fr.ReadLine(buffer))
		{
			line++;
			if (!(eq = strchr(buffer, '=')))
				throw MissingEq();

			switch (buffer[0])
			{
				case 'n':
					snprintf(c.name, max_name_length, "%s", ++eq);
					break;
				case 'h':
					c.max_health = atof(++eq);
					break;
				case 'm':
					c.mvmt_speed = atof(++eq);
					break;
				case 'j':
					c.jump_height = atof(++eq);
					break;
				case 'a':
					c.armor = atof(++eq);
					break;
				//TODO: specials
				default: break;
			}
		}
	}
	catch (ErrorOpeningFile& e) { printf("Could not open character file %s. Exiting", filename); exit(1); }
	catch (MissingEq& e) { printf("Bad line %d in character file %s. Exiting.", line, filename); exit(1); }
}
#endif
