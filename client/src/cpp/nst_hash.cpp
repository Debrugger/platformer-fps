typedef long long int64;

int64 Hash(const char* input)
{
	const char* c;
	int64 i, hash, chash;

	hash = 0xDEADBEEFDEADBEEF;
	for (c = input; *c; c++)
	{
		if(((hash >> 13) ^ (hash >> 3) ^ (hash >> 7)) & 1)
			hash ^= 0x1374F2EE1374F2EE;
		hash = (hash + (unsigned int)(*c) * 0x0811C9DC581C9DC5 + 3) * 0x811C9DC5811C9DC5 + 7;
	}
	chash = hash;

	for (i = 0; i < 8; i++)
		chash ^= hash >> (i << 2);
	return chash;
}

