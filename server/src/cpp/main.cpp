#include "nst_sysinc.h"
#include <vector>
#include "nst_filereader.h"
#include "nst_hashmap.h"
#include "nst_string.h"
#include "nst_contentfile.h"

int main(int argc, char** argv)
{
	String filename = "/run/media/thomas/DEDD-4416/Blender/ShooterRes/lvl_house/examplemap/examplemap.nst";
	ContentFile::GameMapData game_map = ContentFile::BuildMapData(filename);
	printf("map '%s' has %d objects\n", game_map.name.CStr(), game_map.objects.size());
	for (auto it : game_map.objects)
	{
		printf("object %s with coordinates", it.name.CStr());
		for (int i = 0; i < 3; i++)
			printf("%.2f, ", it.translation[i]);
		printf("\n");
	}
}
