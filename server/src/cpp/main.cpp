#include "nst_sysinc.h"
#include <vector>
#include <unordered_map>
#include <functional>
#include "nst_filereader.h"
#include "nst_hashmap.h"
#include "nst_string.h"
#include "nst_datafile.h"
#include "nst_mapdata.h"

int main(int argc, char** argv)
{
	String map_name = argv[1];
	MapData::GameMapData game_map(map_name);
	printf("map '%s' has %lu objects\n", game_map.Name().CStr(), game_map.objects.size());
	for (auto it : game_map.objects)
	{
		printf("object %s with coordinates", it.name.CStr());
		for (int i = 0; i < 3; i++)
			printf("%.2f, ", it.translation[i]);
		printf("\n");
	}
	printf("and %lu animations\n", game_map.animations.size());
}
