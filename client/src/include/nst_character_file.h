#ifndef __CHARACTER_FILE_H
#define __CHARACTER_FILE_H
/*	folder structure should look like this eventually:
							client
								|
		   				 res
						 ____|_______________________
						|				|               |
                world        character        weapon

then in each directory a folder "tex" and "obj" with ALL required textures/.obj's, the data file with objects, coords etc... and texture paths in tex directory
=> every directory is all-in-one and should be independent off everything else */

namespace CharacterFile
{
	const int max_name_length = 50;
	class TempCharacter;
	void Load(char* filename);

	class OpenFileError {};
	class BadName {};
	class BadMeshName {};
	class BadCoords {};
	class BadTextureName {};
}

struct CharacterFile::TempCharacter
{
	struct BodyPart
	{
		char obj_name[max_name_length];
		double coords[3];
      char tex_name[max_name_length];
		BodyPart();
	};
	BodyPart body, rarm, larm, rfoot, lfoot;
	char name[max_name_length];
	char mesh_name[max_name_length];
};

#endif //__CHARACTER_FILE_H
