#include "sysinc.h"
#include "glbuffer.h"
#include "glextensions.h"

GlBuffer::GlBuffer()
{
	ptr = 0;
	handle = 0;
	buffersize = 0;
}


GlBuffer::~GlBuffer()
{
	Clear();
}


bool GlBuffer::Create(int _type, int size)
{
	type = _type;
	Clear();
	glGenBuffers(1, &handle);
	glGetError();
	glBindBuffer(type, handle);
	glBufferData(type, size, 0, GL_STATIC_DRAW);
	glBindBuffer(type, 0);
	if (glGetError() != GL_NO_ERROR)
	{
		Clear();
		return false;
	}

	buffersize = size;
	return true;
}


void GlBuffer::Clear()
{
	Unmap();
	if (handle)
	{
		glDeleteBuffers(1, &handle);
		handle = 0;
	}

	buffersize = 0;
}

void* GlBuffer::Map()
{
	if (!handle || !buffersize)
		return 0;

	if (ptr)
		return ptr;

	glBindBuffer(type, handle);
	ptr = glMapBuffer(type, GL_WRITE_ONLY);
	glBindBuffer(type, 0);
	return ptr;
}

void GlBuffer::Unmap()
{
	if (!ptr)
		return;

	glBindBuffer(type, handle);
	glUnmapBuffer(type);
	glBindBuffer(type, 0);
	ptr = 0;
}
