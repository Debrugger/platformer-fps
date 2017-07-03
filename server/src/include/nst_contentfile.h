#ifndef __CONTENT_FILE_H
#define __CONTENT_FILE_H

namespace ContentFile 
{
	class ErrOpenFile {};
	class BadValue {};

   class ConfigValue;
	struct GameMapObject;
	struct GameMapData;
	struct Point;
	Hashmap<ConfigValue> ParseNextBlock(FileReader& fr);
	std::vector< Hashmap< ConfigValue> > ParseNextSection(FileReader& fr);
	GameMapData BuildMapData(char* filename);
}

class ContentFile::ConfigValue
{
	String val;
	
public:
	void Set(String s)         { val = s; };
	String& GetString()         { return val; };
	int GetInt()               { return atoi(val.CStr()); };
	double GetDouble()         { return atof(val.CStr()); };
	int* GetIntArr();
	double* GetDoubleArr();

	void operator=(String s)   { val = s; };
};


struct ContentFile::GameMapObject
{
	String obj_file_name;
	String texture_diff;
	double translation[3];
	double rotation[3];
	double scale[3];
	//actions and stuff here
};

struct ContentFile::Point
{
	union
	{
		struct { double x, y, z; };
		double coords[3];
	};
	Point() : x(0.0), y(0.0), z(0.0) {};
};

struct ContentFile::GameMapData
{
	std::vector<GameMapObject> objects;
	std::vector<Point> spawnpoints;
};

#endif //__CONTENT_FILE_H
