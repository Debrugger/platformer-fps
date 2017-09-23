#ifndef __MAPDATA_H
#define __MAPDATA_H

namespace MapData
{
	using DataFile::ConfigValue;
	using DataFile::ConfigBlock;
	using DataFile::ConfigBlockList;

	class WrongAniFile { public: String file; WrongAniFile(const String s) : file(s) {}; };

	class GameMapData;
	struct MapObject;
	struct Point;

	struct TempAni
	{ 
		String object;
		String trigger;
		String trigger_args;
		String action;
  		String action_args; 
	};

	class Animation;
	class AnimationTrigger;
	class AnimationAction;
	
	typedef std::unordered_map<std::string, std::function<AnimationTrigger*(String)> > TriggerLookup;
	typedef std::unordered_map<std::string, std::function<AnimationAction*(String)> > ActionLookup;

}

class MapData::GameMapData
{
	TriggerLookup triggers; 
	ActionLookup actions;
	String map_name;
	Hashmap<bool> object_lookup;

	GameMapData();
	void BuildMapData(const String map_name); //get all config values from the files into hashmaps 
	void ExtractMapData(ConfigBlockList& objects, ConfigBlockList& spawns, Hashmap<bool>& object_lookup);
	std::vector<TempAni> ParseAnimations(FileReader& fr);
	void GetAnimations();

public:
	std::vector<Point> spawnpoints;
	std::vector<MapObject> objects;
	std::vector<Animation> animations;

	GameMapData(const String map_name); 
	String Name()        { return map_name; };
};

class MapData::MapObject
{
	//TODO: object list (singly linked or XOR)
	//load data directly into objects when extracting map data
	//texture lookup to reuse same textures (hashmap)
	//stuff to be removed: should be loaded into object immediatly
	String obj_file_name;
	String texture_diff;
	std::vector<double> translation;
	std::vector<double> rotation;
	std::vector<double> scale;

	String name;
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
	Matrix matrix;
public:

	MapObject() : name("NoName"), obj_file_name("default.obj"), texture_diff("default_tex.png"), scale{1.0, 1.0, 1.0} {};
	MapObject(String n, String ofn, String tex_d, std::vector<double> t, std::vector<double> r, std::vector<double> s);
	~MapObject();
	String Name()   { return name; };



	Vector GetPos()                             { Vector ret; ret.x = matrix.m[3][0]; ret.y = matrix.m[3][1]; ret.z = matrix.m[3][2]; return ret; };
	void Move(double x, double y, double z)     { matrix.m[3][0] += x; matrix.m[3][1] += y; matrix.m[3][2] += z; };
	void Move(const Vector& v)                  { matrix.m[3][0] += v.x; matrix.m[3][1] += v.y; matrix.m[3][2] += v.z; };
	void MoveTo(double x, double y, double z)   { matrix.m[3][0] = x; matrix.m[3][1] = y; matrix.m[3][2] = z; };
	void MoveTo(const Vector& v)                { matrix.m[3][0] = v.x; matrix.m[3][1] = v.y; matrix.m[3][2] = v.z; };
	void Rotate(double _x, double _y, double _y, double angle)  { Vector v; v.Set(_x, _y., _z); Rotate(v, angle); };
	void Rotate(const Vector& axis, double angle);
	void Rotate(const double x, const double y, const double z) { Vector v; v.Set(1.0, 0.0, 0.0); Rotate(v, x); v.Set(0.0, 1.0, 0.0); Rotate(v, x); v.Set(0.0, 0.0, 1.0); Rotate(v, z); };
		double PosX()                    { return matrix.PosX(); };
		double PosY()                    { return matrix.PosY(); };
		double PosZ()                    { return matrix.PosZ(); };
		void PosX(double x)              { matrix.PosX(x); };
		void PosY(double y)              { matrix.PosY(y); };
		void PosZ(double z)              { matrix.PosZ(z); };
};

struct MapData::Point
{
	union
	{
		struct { double x, y, z; };
		double coords[3];
	};
};

class MapData::AnimationTrigger
{
public:
	virtual ~AnimationTrigger();
	virtual bool Due() = 0;
};

class MapData::AnimationAction
{
public:
	virtual ~AnimationAction();
	virtual void Execute() = 0;
};


class MapData::Animation
{
	AnimationTrigger& trigger;
	AnimationAction& action;
	Animation();
	MapObject& object;

	public:
	Animation(AnimationTrigger& t, AnimationAction& a, MapObject* parent)
		: trigger(t), action(a), object(*parent) {};
};

#endif //__MAPDATA_H
