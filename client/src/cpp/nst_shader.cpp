#include "sysinc.h"
#include "glextensions.h"
#include "shader.h"

Shader::Shader()
{
	vertex_shader_handle = pixel_shader_handle = handle = 0;
}

Shader::~Shader()
{
	Clear();
}

int Shader::CompileShader(const char* shader_name, int type)
{
	struct stat st;
	int h;
	int status;
	int arr_length[1];
	char* buffer;
	char* arr[1];

	if (::stat(shader_name, &st) != 0)
	{
		printf("Could not find shader '%s'. Exiting.\n", shader_name);
		exit(1);
	}

	if (st.st_size <= 0 || st.st_size >= 65535)
	{
		printf("FATAAAL: shader '%s'\n", shader_name);
		exit(1);
	}

	buffer = new char[st.st_size + 1];
	h = open(shader_name, O_RDONLY);
	if (h < 0)
	{
		printf("FATAAAAAL: could not open shader '%s'\n", shader_name);
		exit(1);
	}
	if (read(h, buffer, st.st_size) != st.st_size)
	{
		printf("FATAAAAAL: could not read shader '%s'\n", shader_name);
		exit(1);
	}
	close(h);

	buffer[st.st_size] = 0;     /* nullterminierung */
	h = glCreateShader(type);
	arr[0] = buffer;
	arr_length[0] = st.st_size;
	glShaderSource(h, 1, arr, arr_length);
	glCompileShader(h);
	glGetObjectParameterivARB(h, GL_OBJECT_COMPILE_STATUS_ARB, &status);
	if (!status)
	{
		printf("FATAAAAAL: could not compile shader '%s'\n", shader_name);
		exit(1);
	}
	return h;


}

void Shader::Load(const char* vertex_shader_name, const char* pixel_shader_name)
{
	int status;
	Clear();
	vertex_shader_handle = CompileShader(vertex_shader_name, GL_VERTEX_SHADER);
	pixel_shader_handle = CompileShader(pixel_shader_name, GL_FRAGMENT_SHADER);

	handle = glCreateProgram();
	glAttachShader(handle, vertex_shader_handle);
	glAttachShader(handle, pixel_shader_handle);
	glLinkProgram(handle);
	glGetObjectParameterivARB(handle, GL_OBJECT_LINK_STATUS_ARB, &status);

	if (!status)
	{
		printf("FATAAAAAL: could not link shader '%s' and '%s'\n", vertex_shader_name, pixel_shader_name);
		exit(1);
	}

	glUseProgram(handle);
	glUniform1i(GetGlUniform("uni_tex_handle"), 0);
}

void Shader::Use()
{
	glUseProgram(handle);
}

void Shader::Clear()
{
	if (vertex_shader_handle)
		glDeleteObjectARB(vertex_shader_handle);
	if (pixel_shader_handle)
		glDeleteObjectARB(pixel_shader_handle);
	if (handle)
		glDeleteObjectARB(handle);

	vertex_shader_handle = 0;
	pixel_shader_handle = 0;
	handle = 0;
}

void Shader::UseNone()
{
	glUseProgram(0);
}

int Shader::GetGlUniform(const char* uni_name)
{
	int l;

	l = glGetUniformLocation(handle, uni_name);
	if (l < 0)
	{
		printf("FATAAAAL: could not find glsl uniform variable '%s'\n", uni_name);
		exit(1);
	}
	return l;
}
