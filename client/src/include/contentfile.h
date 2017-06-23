#ifndef __CONTENT_FILE_H
#define __CONTENT_FILE_H

namespace ContentFile 
{
   class ConfigValue;
	class ErrOpenFile {};
	Hashmap<ConfigValue> ParseFile(char* filename);

}

#endif //__CONTENT_FILE_H
