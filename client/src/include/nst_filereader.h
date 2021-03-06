
/* include guard */
#ifndef __FILEREADER_H
#define __FILEREADER_H

#define FILEREADER_MAX_LINE_LENGTH 8192
#define FILEREADER_BUFFER_SIZE     8192

class FileReader
{
	int handle;
	char *buffer;
	char *actual_position;
	int left_buffer_bytes;

	public:
	FileReader();
	bool Open(const char *filename);
	bool ReadLine(char *destination_line);
	void Close();
};



#endif // __FILEREADER_H




