#ifndef __ANIMATIONS_H
#define __ANIMATIONS_H

namespace MapData
{
	namespace Animations
	{
		class TriggerForever;
		class TriggerInterval;

		class ActionMove;
		class ActionMoveTo;
		class ActionMoveBetween;
	}
}

class MapData::Animations::TriggerForever : public MapData::AnimationTrigger
{
public:
	TriggerForever(String args);
	bool Due();
};

class MapData::Animations::TriggerInterval : public MapData::AnimationTrigger
{
	long int starting_time;
	long int interval;

public:
	TriggerInterval(String args);
	bool Due();
};

class MapData::Animations::ActionMove : public MapData::AnimationAction
{                                                   
public:
	ActionMove(String args);
	void Execute();
};

class MapData::Animations::ActionMoveTo : public MapData::AnimationAction
{                                                   
public:
	ActionMoveTo(String args);
	void Execute();
};

class MapData::Animations::ActionMoveBetween : public MapData::AnimationAction
{                                                   
public:
	ActionMoveBetween(String args);
	void Execute();
};
#endif //__ANIMATIONS_H
