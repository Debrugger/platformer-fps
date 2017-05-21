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

	class OpenFileError {};
}

class CharacterFile::TempCharacter
{
	struct BodyPart
	{
		char obj_name[max_name_length];
		double coords[3];
      char tex_name[max_name_length];
		BodyPart() : obj_name(""), coords[0](0.0), coords[1](0.0), coords[2](0.0), tex_name("rc/default_tex.png");
	};
	BodyPart body, r_arm, l_arm, r_foot, l_foot;
	char name[max_name_length];
};

#endif //__CHARACTER_FILE_H
