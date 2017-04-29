#include "sysinc.h"
#include "filereader.h"

FileReader::FileReader()
{
	handle = -1; /* closed */
	buffer = 0;
	left_buffer_bytes = 0;
}

bool FileReader::Open(const char *filename)
{
	Close();

	handle = open(filename, O_RDONLY);
	if (handle < 0)
	{
		handle = -1;
		printf("sorry, could not open file '%s'\n", filename);
		return false;
	}

	buffer = new char[FILEREADER_BUFFER_SIZE];
	if (!buffer)
	{
		Close();
		printf("could not allocate %d bytes of memory\n", FILEREADER_BUFFER_SIZE);
		return false;
	}

	actual_position = 0;
	return true;
}

void FileReader::Close()
{
	if (buffer)
	{
		delete [] buffer;
		buffer = 0;
	}

	if (handle >= 0)
	{
		close(handle);
		handle = -1;
	}
}

bool FileReader::ReadLine(char *destination_line)
{
	int r, i;

	if (handle < 0)
	{
		printf("ERROR: called ReadLine() without open file!!!\n");
		return false;
	}
	i = 0;
	while (true)
	{
		for (; i < FILEREADER_MAX_LINE_LENGTH - 1 && left_buffer_bytes > 0 && *actual_position != '\n'; i++, left_buffer_bytes--)
			destination_line[i] = *actual_position++;

		if (i == FILEREADER_MAX_LINE_LENGTH - 1 || (left_buffer_bytes > 0 && actual_position && *actual_position == '\n'))
		{
			left_buffer_bytes--;
			actual_position++;
			destination_line[i] = 0;
			return true;
		}

		if (left_buffer_bytes != 0)
		{
			printf("FATALER PROGRAMMIERFEHLER!!!!!! DARF NICHT PASSIEREN in FileReader::ReadLine()\n");
			exit(1);
		}

		r = read(handle, buffer, FILEREADER_BUFFER_SIZE);
		if (r <= 0)
		{
			/* wenn destination_line ne halbe Zeile enth?lt, dann kann diese noch ausgeliefert werden! */
			if (i)
			{
				destination_line[i] = 0;
				return true;
			}
			return false;
		}
		left_buffer_bytes = r;
		actual_position = buffer;
	}
}
