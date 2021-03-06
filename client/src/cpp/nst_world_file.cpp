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
#include "world_file.h"
#define SPAWNPOINTS_HEADER				"[Spawnpoints]"
#define MAX_SPAWNPOINTS					25

#ifdef CONCEPT
/* =======maybe better?===========*/
class File
{
	void Value(string _key);
	void operator>>(string);
	void operator>>(double*);
};

File wf;
string name;
double coords[3];
wf.Value("name") >> name;
wf.Value("coords") >> coords; //this then does everything automatically
#endif

void WorldFile::Load(const char* filename)
{
	using namespace WorldFile;
	FileReader fr;
	char buffer[FILEREADER_MAX_LINE_LENGTH];
	int line = 0;
	char* eq;
	char* co;
	TempObject o;
	int nb_objects = 0;
	bool in_spawn_section = false;
	int nb_weapon_spawns = 0;
	int nb_player_spawns = 0;
	Spawnpoint weapon_spawns[MAX_SPAWNPOINTS];
	Spawnpoint player_spawns[MAX_SPAWNPOINTS];

	if (!fr.Open(filename)) throw OpenFileError();
	while (fr.ReadLine(buffer))
	{
		line++;
		try
		{
			if (strcmp(buffer, SPAWNPOINTS_HEADER))
				in_spawn_section = true;
			if (!in_spawn_section) switch(buffer[0])
			{
				case 'n':
					if (o.has_name && o.has_mesh && o.has_pos && o.has_rot && o.has_sca) CreateObject(&o); 
					nb_objects++;
					if ((eq = strchr(buffer, '=')))
						snprintf(o.name, max_name_length, "%s", ++eq);
					else
						throw ObjectNameWrong();
					printf("Name of object: %s\n", o.name);
					o.has_name = true;
					break;

				case 'm':
					if ((eq = strchr(buffer, '=')))
						snprintf(o.mesh, max_name_length, "%s", ++eq);
					else throw MeshNameWrong();
					o.has_mesh = true;
					break;

				case 't':
					if ((eq = strchr(buffer, '=')))
						snprintf(o.texture, max_name_length, "%s", ++eq);
					else
						throw TextureWrong();
					printf("Object Texture: %s\n", o.texture);
					break;
				case 'c':
					if ((eq = strchr(buffer, '=')))
					{
						co = eq;
						for (int i = 0; i < 3; i++)
						{
							o.coords[i] = atof(++co);
							printf("Found coordinate %f\n", o.coords[i]);
							co = strchr(co, ',');
							if (!co && i != 2) throw PosCoordsWrong();
						}
					}
					o.has_pos = true;
					break;

				case 's':
					if ((eq = strchr(buffer, '=')))
					{
						co = eq;
						for (int i = 0; i < 3; i++)
						{
							o.scale[i] = atof(++co);
							co = strchr(co, ',');
							if (!co && i != 2) throw ScaCoordsWrong();

						}
					}
					o.has_sca = true;
					break;

				case 'r':
					if ((eq = strchr(buffer, '=')))
					{
						co = eq;
						for (int i = 0; i < 3; i++)
						{
							o.rotation[i] = atof(++co);
							co = strchr(co, ',');
							if (!co && i != 2) throw RotCoordsWrong();
						}
					}
					o.has_rot = true;
					break;
				default: break;
			}
			if (in_spawn_section)
			{
				switch (buffer[0])
				{
					case 'p':
						if ((eq = strchr(buffer, '=')) && nb_player_spawns < MAX_SPAWNPOINTS)
						{
							co = eq;
							for (int i = 0; i < 3; i++)
							{
								player_spawns[nb_player_spawns].coords[i] = atof(++co);
								printf("Found player spawn coordinate %f\n", o.coords[i]);
								co = strchr(co, ',');
								if (!co && i != 2) throw SpawnpointWrong();
							}
							nb_player_spawns++;
						}
						else throw SpawnpointWrong();
						break;
					case 'w':
						if ((eq = strchr(buffer, '=')) && nb_weapon_spawns < MAX_SPAWNPOINTS)
						{
							co = eq;
							for (int i = 0; i < 3; i++)
							{
								weapon_spawns[nb_weapon_spawns].coords[i] = atof(++co);
								printf("Found weapon spawn coordinate %f\n", o.coords[i]);
								co = strchr(co, ',');
								if (!co && i != 2) throw SpawnpointWrong();
							}
							nb_weapon_spawns++;
						}
						else throw SpawnpointWrong();
						break;
					default: break;
				}
			}
		}
		catch(OpenFileError& e)		{ printf ("Could not open world file %s. Exiting.\n", filename); exit(1); }
		catch(ObjectNameWrong& e)	{ printf("Name in world file %s wrong (too long? no longer than %d allowed). Exiting because shit is probably broken.\n", filename, max_name_length); exit(1); }
		catch(MeshNameWrong& e)		{ printf("Texture	name in world file %s wrong (too long? no longer than %d allowed). Exiting because shit is probably broken.\n", filename, max_name_length); exit(1); }
		catch(TextureWrong&e)		{ printf("Mesh name in world file %s wrong (too long? no longer than %d allowed). Exiting because shit is probably broken.\n", filename, max_name_length); exit(1); }
		catch(PosCoordsWrong& e)	{ printf ("Not enough coordinates in world file %s:%d for object. Exiting because shit is probably broken.\n", filename, line); exit(1); }
		catch(ScaCoordsWrong& e)	{ printf ("Not enough coordinates in world file %s:%d for object scaling. Exiting because shit is probably broken.\n", filename, line); exit(1); }
		catch(RotCoordsWrong& e)	{ printf ("Not enough coordinates in world file %s:%d for object rotation. Exiting because shit is probably broken.\n", filename, line); exit(1); }
		catch(SpawnpointWrong& e)	{ printf ("Spawnpoint in world file %s:%d wrong (too long? no longer than %d allowed. Exiting.", filename, line, MAX_SPAWNPOINTS); exit(1); }

	}
	fr.Close();
	if (o.has_name && o.has_mesh && o.has_pos && o.has_rot && o.has_sca) CreateObject(&o);
	printf("Loaded %d objects from world file.\n", nb_objects);
}

void WorldFile::CreateObject(const WorldFile::TempObject* t)
{
	if (!t->mesh[0] || !t->name[0])
		return;
	printf ("Attempting to create model with mesh %s, name %s\n", t->mesh, t->name);

	Model m;
	Object* o = new Object;
	o->texture = new Texture;
	o->mesh = new Mesh;

	char obj_name[max_name_length + 4];
	strcpy(obj_name,  t->mesh);
	char* n = strchr(obj_name, 0);
	char e[5] = ".obj";
	strcpy(n, e);

	m.Load(obj_name);
	m.ToMesh(o->mesh);
	o->shader = &shader; //TODO: have these in world file
	o->texture->Load(t->texture); //TODO
	o->MoveTo(t->coords[0], t->coords[1], t->coords[2]);
	o->Rotate(t->rotation[0], t->rotation[2], t->rotation[1]); //swapping y and z
	//o->Scale(t->scale[0], t->scale[1], t->scale[2]); TODO implement Scale
	printf("Created object %s\n", t->name);
}
