#include "sysinc.h"
#include "hashmap.h"

template<typename T> T* Hashmap<T>::Fetch(char* _key, bool* created)
{
	typedef long long int64;
	void** node;
	if (!tree_root) 
	{
		tree_root = new void*[16]
		if (created) *created = true;
	}
	int64 hash = Hash(key);

	node = tree_root;
	for (int i = 0; i < 16; i++)
	{
		int nibble = (hash >> 4 * i) & 0xF;
		if (!node[nibble])
			node[nibble] = new void*[16];
		node = static_cast<void*>(node[nibble]);
	}
	return static_cast<T*>(node);
}
