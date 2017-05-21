#ifndef __CHARACTER_FILE_H
#define __CHARACTER_FILE_H
/*
	folder structure for server:
						server
					_____|______________
              |          |        |
				  map			char      weapon
				  				char1.dat
	*/

namespace CharacterFile
{
	const int max_name_length = 50;
	struct TempCharacter
	{
		TempCharacter();
		char name[max_name_length];
		int max_health;
		double mvmt_speed;
      double jump_height;
		float armor;
		bool jetpack; //specials
	};
	void Load(char* filename);

	class ErrorOpeningFile {};
	class MissingEq {};
}

#endif //__CHARACTER_FILE_H
