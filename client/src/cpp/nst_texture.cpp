#include "sysinc.h"
#include <png.h>
#include "texture.h"
#include "glextensions.h"

Texture::Texture()
{
	gl_handle = 0;
	file_handle = -1;
	width = height = 0;
	internal_temporary_buffer = 0;
}

Texture::~Texture()
{
	if (internal_temporary_buffer)
		delete [] internal_temporary_buffer;
}

static void PngInfoCallback(png_struct* png, png_info* png_info)
{
	png_uint_32 w, h;
	int bits_per_pixel;
	int color_type;
	Texture* texture;
	texture = (Texture*)png_get_progressive_ptr(png);

	png_get_IHDR(png, png_info, &w, &h, &bits_per_pixel, &color_type, 0, 0, 0);
	texture->width = w;
	texture->height = h;

	if (color_type == PNG_COLOR_TYPE_GRAY && bits_per_pixel < 0)
		png_set_expand_gray_1_2_4_to_8(png);
	if (bits_per_pixel == 16)
		png_set_strip_16(png);
	else if (bits_per_pixel < 8)
		png_set_packing(png);
	if (color_type & PNG_COLOR_MASK_PALETTE)
		png_set_palette_to_rgb(png);
	if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
		texture->GenerateTemporaryImage(w * h * 4, GL_RGBA, 4);
	else
		texture->GenerateTemporaryImage(w * h * 3, GL_RGB, 3);
	png_start_read_image(png);
	//    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_RGB_ALPHA)
	//        png_set_bgr(png);
}

static void PngLineCallback(png_struct* png, png_byte* row, png_uint_32 row_num, int pass)
{
	int n;
	Texture* texture;
	texture = (Texture*)png_get_progressive_ptr(png);
	n = texture->width * texture->bytes_per_pixel;
	memcpy(texture-> internal_temporary_buffer + row_num * n, row, n);
}

static void PngEndCallback(png_struct* png, png_info* png_info)
{
}

static void PngWarningCallback(png_struct* png, const char* warning_message)
{
}

static void PngErrorCallback(png_struct* png, const char* error_message)
{
	printf("FATAAAAAAL: error in reading png file\n");
}

bool Texture::Load(const char* filename)
{
	png_struct* png;
	png_info* png_info;
	char* buffer;
	int buffer_size;      
	float max_anisotropy;
	/*die png einlesen in buffer*/
	Clear();

	buffer = new char[FILEREADER_TEXURE_BUFFER_SIZE];
	if (!buffer)
	{
		printf("FATAAAAAAL: could not allocate enough memory for '%s'\n", filename);
		return false;
	}

	file_handle = open(filename, O_RDONLY);
	if (file_handle < 0)
	{
		delete [] buffer;
		printf("FATAAAAL: could not open png %s\n", filename);
		return false;
	}

	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if (!png)
	{
		delete [] buffer;
		printf("FATAAAAAL: could not initialize png-info struct to load texture '%s'\n", filename);
		file_handle = -1;
		return false;
	}
	png_info = png_create_info_struct(png);
	if (!png_info)
	{
		delete [] buffer;
		png_destroy_read_struct(&png, 0, 0);
		return false;
	}

	png_set_progressive_read_fn(png, this, PngInfoCallback, PngLineCallback, PngEndCallback);
	png_set_error_fn(png, this, PngErrorCallback, PngWarningCallback);

	while ((buffer_size = read(file_handle, buffer, FILEREADER_TEXURE_BUFFER_SIZE)) > 0)
		png_process_data(png, png_info, (png_byte*)buffer, buffer_size);
	close(file_handle);
	file_handle = -1;
	png_free_data(png, png_info, PNG_FREE_ALL, -1);
	/*eingelesene png in opengl rein*/

	glGenTextures(1, &gl_handle);
	glBindTexture(GL_TEXTURE_2D, gl_handle);
	glTexImage2D(GL_TEXTURE_2D, 0, bytes_per_pixel, width, height, 0, gl_format, GL_UNSIGNED_BYTE, internal_temporary_buffer);
	gluBuild2DMipmaps(GL_TEXTURE_2D, bytes_per_pixel, width, height, gl_format, GL_UNSIGNED_BYTE, internal_temporary_buffer);
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);

	delete [] internal_temporary_buffer;
	internal_temporary_buffer = 0;
	return true;   
}

void Texture::Clear()
{
	if (gl_handle > 0)
	{
		glDeleteTextures(1, &gl_handle);
		gl_handle = 0;
	}
}

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, gl_handle);
}

void Texture::UseNone()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::GenerateTemporaryImage(int size, GLenum _gl_format, int _bytes_per_pixel)
{
	internal_temporary_buffer = new char[size];
	gl_format = _gl_format;
	bytes_per_pixel = _bytes_per_pixel;
}
