#ifndef __WORLD_FILE_H
#define __WORLD_FILE_H

const int name_length = 20;
struct TempObject
{
	char name[name_length];
	char mesh[name_length];
	double coords[3];
	double scale[3];
	double rotation[3];
	TempObject() : name(""), mesh(""), coords{0.0, 0.0, 0.0}, scale{1.0, 1.0, 1.0}, rotation{0.0, 0.0, 0.0} {}
};

void LoadWorldFile(const char* filename);
void CheckAndCreate(const TempObject* t);

#endif //__WORLD_FILE_H
