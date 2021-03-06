#ifndef __HASHMAP_H
#define __HASHMAP_H

/*-----------------Hashmap class----------------*/
/*--------------v1.0-2017-06-17------------------*/


typedef long long int64;

int64 Hash(const char* input);

template<typename T> class Hashmap
{
	T* GetOrFetch(const char* _key, bool* _created, bool _create = false);
	bool DeleteNode(int _depth, int64 _k, void** _node, bool* _deleted);

	void** tree_root;
	int64 size;
public:
	Hashmap() : tree_root(0), size(0)          {};
	~Hashmap() { Clear(); };
	T* Get(const char* _key)				       { return GetOrFetch(_key, 0, false); };
	T* Fetch(const char* _key, bool* _created = 0) { return GetOrFetch(_key, _created, true); };
	bool Delete(const char* _key);
	void Clear();
	size_t Size() { return size; };

	T& operator[](const char* key)  	       { return *Fetch(key, 0); };
	const T& operator[](const char* key) const    { return *Get(key); };
};

template<typename T> T* Hashmap<T>::GetOrFetch(const char* _key, bool* _created, bool _create)
{
	void** node;
	int nibble;

	if (_created) *_created = false;
	if (!tree_root) 
	{
		if (_create)
		{
			tree_root = new void*[16];
			for (int i = 0; i < 16; ++i)
				tree_root[i] = 0;
			if (_created) *_created = true;
		}
		else return 0;
	}

	int64 hash = Hash(_key);
	node = tree_root;

	for (int i = 0; i < 16; i++)
	{
		nibble = (hash >> (4 * i)) & 0xF;
		if (!node[nibble])
		{
			if (_create)
			{
				node[nibble] = new void*[16];
				for (int j = 0; j < 16; ++j)
					((void**)node[nibble])[j] = 0;
				if (_created) *_created = true;
			}
			else return 0;
		}
		node = static_cast<void**>(node[nibble]);
	}
	if (!node[nibble])
	{
		if (_create)
		{
			if (_created) *_created = true;
			node[nibble] = new T;
			size++;
		}
		else return 0;
	}
	return static_cast<T*>(node[nibble]);
}

template<typename T> bool Hashmap<T>::DeleteNode(int _depth, int64 _k, void** _node, bool* _deleted)
{
	int i;
	int64 real_k = _k & 0xF;  //k is the hash we're getting and we're cutting off everything but the leading 4 bits

	if (!_depth)  //if we're in the uppermost layer and the node we want to delete exists, delete it
	{
		if (_node[real_k])
		{
			delete (T*)(_node[real_k]);
			_node[real_k] = 0;
			*_deleted = true;
			size--;
		}
	}
	else
	{
		if (_node[real_k] && DeleteNode(_depth - 1, _k >> 4, (void**)_node[real_k], _deleted))   //if the node exists
		{
			delete [] static_cast<void**>(_node[real_k]);
			_node[real_k] = 0;
		}
	}

	for (i = 0; i < 16; i++)
	{
		if (_node[i])
			return false;
	}
	//_node[real_k] = 0;
	return true;
}

template<typename T> bool Hashmap<T>::Delete(const char* _key)
{
	bool ret = false;
	if (!tree_root) return false;

	int64 hash = Hash(_key);
	if (DeleteNode(16, hash, tree_root, &ret))
	{
		delete [] tree_root;
		tree_root = 0;
	}
	return ret;
}

template<typename T> void Hashmap<T>::Clear()
{
	struct Walker
	{
		int branch;
		void** node;
	};
	Walker stack[17];
	void** n = tree_root;
	int p = 0;

	if (!tree_root)
		return;

	for (int i = 0; i < 17; i++)
		stack[p].branch = 0;

	while (true)
	{
		if (n[stack[p].branch])
		{
			if (p == 16)
			{
				delete (T*)(n[stack[p].branch]);
				n[stack[p].branch] = 0;
			}
			else
			{
				stack[p].node = n;
				n = (void**)n[stack[p].branch];
				p++;
				stack[p].branch = 0;
			}
		}
		else
		{
			stack[p].branch++;
			if (stack[p].branch == 16)
			{
				p--;
				if (0 > p) 
				{
					size = 0;
					delete [] tree_root;
					tree_root = 0;
					return;
				}
				n = stack[p].node;
				if (p >= 16)
					printf("HASHMAP: BROKEN\n");
				else
				{
					delete[] (void**)n[stack[p].branch];
					n[stack[p].branch] = 0;
				}
			}
		}
	}
}
#endif //__HASHMAP_H
