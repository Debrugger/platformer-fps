#include "nst_sysinc.h"
#include <vector>
#include <unordered_map>
#include <functional>
#include "nst_hashmap.h"
#include "nst_filereader.h"
#include "nst_string.h"
#include "nst_datafile.h"
#include "nst_mapdata.h"
#include "nst_animations.h"

using namespace MapData::Animations;

TriggerForever::TriggerForever(String args)
{
	printf("Initializing new trigger: FOREVER\n");
}

bool TriggerForever::Due()
{
	return true;
}

TriggerInterval::TriggerInterval(String args)
{
	starting_time = 0; //NEEDS TO BE SET WHEN GAME STARTS
	printf("Initializing new trigger: INTERVAL with args '%s'\n", args.CStr());
	interval = atol(args);
}

bool TriggerInterval::Due()
{
}

ActionMove::ActionMove(String args)
{
	printf("Initializing new action: MOVE with args '%s'\n", args.CStr());
}

void ActionMove::Execute()
{
	printf("Executing action MOVE.\n");
}
