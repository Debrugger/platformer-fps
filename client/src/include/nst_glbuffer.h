#ifndef __GLBUFFER_
#define __GLBUFFER_

struct GlBuffer
{
	void* ptr;
	GLuint handle;
	int buffersize;
	int type;

	GlBuffer();
	~GlBuffer();

	bool Create(int _type, int size);
	void Clear();

	void* Map();
	void Unmap();
};

#endif //__GLBUFFER_
