#ifndef __WORLD_FILE_H
#define __WORLD_FILE_H

namespace WorldFile
{
	const int max_name_length = 50;
	struct TempObject;
	void CreateObject(const TempObject* t);
	void Load(const char* filename);

	struct TempObject
	{
		bool has_name;
		bool has_mesh;
		bool has_pos;
		bool has_rot;
		bool has_sca;

		char name[max_name_length];
		char mesh[max_name_length];
		double coords[3];
		double scale[3];
		double rotation[3];
		TempObject() : has_name(false), has_mesh(false), has_pos(false), has_rot(false), has_sca(false), name(""), mesh(""), coords{0.0, 0.0, 0.0}, scale{1.0, 1.0, 1.0}, rotation{0.0, 0.0, 0.0} {}
	};

	class OpenFileError {};
	class ObjectNameWrong {};
	class MeshNameWrong {};
	class PosCoordsWrong {};
	class ScaCoordsWrong {};
	class RotCoordsWrong {};
}

#endif //__WORLD_FILE_H
