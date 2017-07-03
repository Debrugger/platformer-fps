#ifndef __SHADER_H
#define __SHADER_H

class Shader
{
	int vertex_shader_handle;
	int pixel_shader_handle;
	int handle; /* for whole render pipeline */

	public:
	Shader();
	~Shader();

	void Load(const char* vertex_shader_name, const char* pixel_shader_name);
	void Use();
	void Clear();
	static void UseNone();
	int GetGlUniform(const char* uni_name);
	static int CompileShader(const char* shader_name, int type);
};

#endif // __SHADER_H c
