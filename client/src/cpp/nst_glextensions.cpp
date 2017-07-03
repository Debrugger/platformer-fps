#include "sysinc.h"
#include "glextensions.h"

//void  (*glBindBuffer)(int, GLuint);
//void  (*glGenBuffers)(int, GLuint*);
//void  (*glBufferData)(int, size_t, const void*, GLenum);
//void  (*glDeleteBuffers)(int, GLuint*);
//void* (*glMapBuffer)(GLenum, GLenum);
//void  (*glUnmapBuffer)(GLenum);
//int   (glCompileShader)(GLenum);
//void  (glShaderSource)(int, int, char**, char**);

//static void *GetGlExtension(const char* function_name)
//{
//	void(*ret)();
//	ret = glXGetProcAddress((const GLubyte*)function_name);
//	if (!ret)
//	{
//		printf("FATAL: gl_extension '%s' not found\n", function_name);
//		exit(1);
//	}
//	return (void *)ret;
//}

void GetGlExtensions()
{
	//glBindBuffer        = (void  (*)(int, GLuint))GetGlExtension("glBindBuffer");
	//glGenBuffers        = (void  (*)(int, GLuint*))GetGlExtension("glGenBuffers");
	//glBufferData        = (void  (*)(int, size_t, const void*, GLenum))GetGlExtension("glBufferData");
	//glMapBuffer         = (void* (*)(GLenum, GLenum))GetGlExtension("glMapBuffer");
	//glUnmapBuffer       = (void  (*)(GLenum))GetGlExtension("glUnmapBuffer");
	//glDeleteBuffers     = (void  (*)(int, GLuint*))GetGlExtension("glDeleteBuffers");
	//glCreateShader      = (int   (*)(GLenum)) GetGlExtension("glCreateShader");
}
