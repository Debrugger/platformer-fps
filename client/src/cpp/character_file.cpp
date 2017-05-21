#include "sysinc.h"
#include "qtinc.h"
#include "filereader.h"
#include "glbuffer.h"
#include "vector.h"
#include "matrix.h"
#include "mesh.h"
#include "model.h"
#include "shader.h"
#include "glglobals.h"
#include "texture.h"
#include "object.h"
#include "character_file.h"
/* character file:
 name= should then be synced with server to figure out max health, mvmt speed etc...
 mbody=name of central body object
 mrfoot=mesh for right foot
 mlfoot=mesh for left foot
 mrarm=
 mlarm=
 crfoot=coords of rfoot relative to body origin
 clfoot
 crarm
 clarm
 tbody=texture for body in tex directory
 trfoot
 tlfoot
 trarm
 tlarm
 */

CharacterFile::Load(char* filename)
{
	Filereader fr;
	char* eq;
	char* co;
	char buffer[FILEREADER_MAX_LINE_LENGTH];
	TempCharacter c;
	BodyPart* bp;

	try
	{
		if (!fr.Open(filename))
			throw OpenFileError();
		while (fr.Readline(buffer))
		{
			switch (buffer[0])
			{
				case 'n': //name
					if (!(eq = strchr(buffer, '='))) throw BadName();
					snprintf(c.name, max_name_length, "%s", ++eq);
					break;
				case 'm': //mesh
					if (!(eq = strchr(buffer, '='))) throw BadMesh();
					snprintf(c.mesh, max_name_length, "%s", ++eq);
					break;
				case 'c': //coords  crfoot=
					if (!(eq = strchr(buffer, '='))) throw BadCoords();
					co = eq;
					switch (buffer[2])
					{
						case 'f': //foot
							if (buffer[1] == 'l') bp = &c.lfoot;
							else bp = &c.rfoot;
							for (int i = 0; i < 3; i++)
								bp->coords[i] = atof(++co);
							break;
						case 'a': //arm
							if (buffer[1] == 'l') bp = &c.larm;
							else bp = &c.rarm;
							for (int i = 0; i < 3; i++)
								bp->coords[i] = atof(++co);
							break;
					}
					break;
				case 't': //texture
					if (!(eq = strchr(buffer, '='))) throw BadTexture();
					co = eq;
					switch (buffer[2])
					{
						case 'f': //foot
							if (buffer[1] == 'l') bp = &c.lfoot;
							else bp = &c.rfoot;
							snprintf(bp->tex_name, max_name_length, "%s", ++eq);
							break;
						case 'a': //arm
							if (buffer[1] == 'l') bp = &c.larm;
							else bp = &c.rarm;
							snprintf(bp->tex_name, max_name_length, "%s", ++eq);
							break;
					}
					break;
			}
		}
	}
}
