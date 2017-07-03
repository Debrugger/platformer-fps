#include "sysinc.h"
#include "goodstring.h"
#include "hashmap.h"
#include "contentfile.h"
#include "gameinit.h"

void InitGame::InitWorld()
{
	Hashmap<ContentFile::ConfigValue> parsed = ContentFile::ParseFile("world.dat");
	//for (int i = 0; i < 3; i++)
	printf("coord: %.2f\n", parsed.Get("coords")->GetDoubleArr()[0]);
}
