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
public:
	String name;
	String obj_file_name;
	String texture_diff;
	std::vector<double> translation;
	std::vector<double> rotation;
	std::vector<double> scale;

	MapObject() : name("NoName"), obj_file_name("default.obj"), texture_diff("default_tex.png"), scale{1.0, 1.0, 1.0} {};
	MapObject(String n, String ofn, String tex_d, std::vector<double> t, std::vector<double> r, std::vector<double> s);
	~MapObject();
	String Name()   { return name; };
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
