#ifndef __TEXTURE_H
#define __TEXTURE_H

#define FILEREADER_TEXURE_BUFFER_SIZE   32768

class Texture
{
	GLuint gl_handle;
	int file_handle;

	public:
	int width, height;
	int bytes_per_pixel;
	char* internal_temporary_buffer;

	Texture();
	~Texture();

	void Clear();
	void GenerateTemporaryImage(int size, GLenum _gl_format, int _bytes_per_pixel);
	void Use();
	static void UseNone();   
	bool Load(const char* filename);
	GLenum gl_format;
};

#endif // __TEXTURE_H
