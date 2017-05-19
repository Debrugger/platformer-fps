#ifndef __WORLD_FILE_H
#define __WORLD_FILE_H

namespace WorldFile
{
	const int max_name_length = 50;
	struct TempObject;
	void CreateObject(const TempObject* t);
	void Load(const char* filename);
	struct TempObject;
	struct Spawnpoint;

	class OpenFileError {};
	class ObjectNameWrong {};
	class MeshNameWrong {};
	class TextureWrong {};
	class PosCoordsWrong {};
	class ScaCoordsWrong {};
	class RotCoordsWrong {};
	class SpawnpointWrong {};
}

struct WorldFile::TempObject
{
	bool has_name;
	bool has_mesh;
	bool has_pos;
	bool has_rot;
	bool has_sca;
	bool is_platform;
	bool is_jump;

	char name[max_name_length];
	char mesh[max_name_length];
	char texture[max_name_length];
	double coords[3];
	double scale[3];
	double rotation[3];
	TempObject() : has_name(false), has_mesh(false), has_pos(false), has_rot(false), has_sca(false), is_platform(false), is_jump(false), name(""), mesh(""), texture("rc/default_tex.png"), coords{0.0, 0.0, 0.0}, scale{1.0, 1.0, 1.0}, rotation{0.0, 0.0, 0.0} {}
};

struct WorldFile::Spawnpoint
{
	union
	{
		struct
		{
			double x, y, z;
		};
		double coords[3];
	};
};
#endif //__WORLD_FILE_H
