#include "sysinc.h"
#include "filereader.h"
#include "vector.h"
#include "glbuffer.h"
#include "mesh.h"
#include "model.h"


Model::Model()
{
	vertex_array = 0;
	index_array = 0;
	count_vertex_array = 0;
	count_index_array = 0;
}


Model::~Model()
{
	if (vertex_array)
		delete [] vertex_array;

	if (index_array)
		delete [] index_array;
}



bool Model::Load(const char* from_file)
{
	FileReader fr;
	char line[FILEREADER_MAX_LINE_LENGTH];
	int count_spaces;
	int current_vertex;
	int current_triangle;
	int current_texcoord;
	int col;
	int i, q;
	char* nextn;
	Vector* vertex_buffer;
	Vector2d* texcoord_buffer;
	Triangle* index_buffer;
	int count_vertices;
	int count_texcoords;
	int count_triangles;
	int triangle, wedge;
	TexLookup* tex_lookup_array;
	int tex_lookup_array_size;
	int tex_lookup_array_size_internal;
	struct stat stat_cache, stat_obj;

	min_x = min_y = min_z = +INFINITY;
	max_x = max_y = max_z = -INFINITY;

	printf("Model [%p]: loading '%s' ...\n", this, from_file);

	/* try the cache-version of the obj ... */
	/* "cache/[from_file].yfq$ARCH"            */

	snprintf(line, FILEREADER_MAX_LINE_LENGTH, "cache/%s.yfq%s", from_file, ARCH);

	if (stat(line, &stat_cache) == 0)
	{
		if (stat(from_file, &stat_obj) != 0)
			return false;
		if (stat_cache.st_mtime >= stat_obj.st_mtime)
		{
			/* use the cache */
			i = open(line, O_RDONLY);
			if (i >= 0)
			{
				if (read(i, &count_vertex_array, 2 * sizeof(int)) != 2 * sizeof(int))
				{
					close(i);
					goto load_normal_obj;
				}

				if (count_vertex_array < 3 || count_vertex_array > 1000000)
					goto load_normal_obj;
				if (count_index_array < 1 || count_index_array > 1000000)
					goto load_normal_obj;
				vertex_array = new Vertex[count_vertex_array];
				index_array = new int[count_index_array];
				if (read(i, vertex_array, count_vertex_array * sizeof(Vertex)) != count_vertex_array * (signed int)sizeof(Vertex))
				{
					delete [] vertex_array;
					delete [] index_array;
					close(i);
					goto load_normal_obj;
				}

				if (read(i, index_array, count_index_array * sizeof(int)) != count_index_array * (signed int)sizeof(int))
				{
					delete [] vertex_array;
					delete [] index_array;
					close(i);
					goto load_normal_obj;
				}

				printf("using %s\n", line);
				close(i);
				for (i = 0; i < count_vertex_array; i++)
				{
					if (min_x > vertex_array[i].x) min_x = vertex_array[i].x;
					if (min_y > vertex_array[i].y) min_y = vertex_array[i].y;
					if (min_z > vertex_array[i].z) min_z = vertex_array[i].z;
					if (max_x < vertex_array[i].x) max_x = vertex_array[i].x;
					if (max_y < vertex_array[i].y) max_y = vertex_array[i].y;
					if (max_z < vertex_array[i].z) max_z = vertex_array[i].z;
				}
				return true;
			}
		}
	}


load_normal_obj:
	if (!fr.Open(from_file))
	{
		return false;
		printf ("bei open raus\n");
	}

	if (vertex_array)
		delete [] vertex_array;

	if (index_array)
		delete [] index_array;

	count_vertices = 0;
	count_texcoords = 0;
	count_triangles = 0;
	count_vertex_array = 0;
	count_index_array = 0;

	while (fr.ReadLine(line))
	{
		switch (line[0])
		{
			case 'v':
				if (line[1] == ' ')
					count_vertices++;
				else if (line[1] == 't' && line[2] == ' ')
					count_texcoords++;
				break;

			case 'f':
				if (line[1] != ' ')
					break;
				count_spaces = 0;
				for (i = 0; line[i]; i++)
				{
					if (line[i] == ' ' && line[i + 1] != ' ' && line[i + 1] != 0)
						count_spaces++;
				}

				if (count_spaces > 4)
				{
					return false;
				}
				else if (count_spaces == 4)
					count_triangles += 2;
				else if (count_spaces == 3)
					count_triangles++;
				else
				{
					return false;
				}
				break;
		}
	}

	if (count_vertices <= 0 || count_triangles <= 0)
		return false;
	vertex_buffer = new Vector[count_vertices];

	if (count_texcoords > 0)
		texcoord_buffer = new Vector2d[count_texcoords];
	else
		texcoord_buffer = 0;

	index_buffer = new Triangle[count_triangles];

	if (!fr.Open(from_file))
		return false;

	current_vertex = 0;
	current_texcoord = 0;
	current_triangle = 0;
	while (fr.ReadLine(line))
	{
		switch (line[0])
		{
			case 'v':
				if (line[1] == ' ')
				{
					col = 0;
					for (i = 1; line[i]; i++)
					{
						if (line[i] == ' ' && line[i + 1] != ' ' && col < 3)
							vertex_buffer[current_vertex].v[col++] = atof(line + i + 1);
					}
					if (min_x > vertex_buffer[current_vertex].x) min_x = vertex_buffer[current_vertex].x;
					if (min_y > vertex_buffer[current_vertex].y) min_y = vertex_buffer[current_vertex].y;
					if (min_z > vertex_buffer[current_vertex].z) min_z = vertex_buffer[current_vertex].z;

					if (max_x < vertex_buffer[current_vertex].x) max_x = vertex_buffer[current_vertex].x;
					if (max_y < vertex_buffer[current_vertex].y) max_y = vertex_buffer[current_vertex].y;
					if (max_z < vertex_buffer[current_vertex].z) max_z = vertex_buffer[current_vertex].z;

					current_vertex++;
				}
				else if (line[1] == 't' && line[2] == ' ')
				{
					col = 0;
					for (i = 2; line[i]; i++)
					{
						if (line[i] == ' ' && line[i + 1] != ' ' && col < 2)
							texcoord_buffer[current_texcoord].v[col++] = atof(line + i + 1);
					}
					current_texcoord++;
				}
				break;

			case 'f':
				/*       f 2/3 3/4 7/1 1/1 */
				/* oder  f 4 5 6 */
				/* oder  f 2/3/4 3/3/1 1/1/1 */
				/* oder  f 5//12 3//4 4//1 */
				if (line[1] != ' ')
					break;
				col = 0;
				for (i = 1; line[i]; i++)
				{
					if (line[i] == ' ' && line[i + 1] != ' ')
					{
						nextn = strchr(line + i + 1, '/');
						if (col < 3)
						{
							index_buffer[current_triangle].t[col] = q = atoi(line + i + 1) - 1;
							if (texcoord_buffer)
							{
								if (nextn)
									index_buffer[current_triangle].tx[col] = atoi(nextn + 1) - 1;
								else
									index_buffer[current_triangle].tx[col] = q;
							}

							col++;
						}
						else if (col == 3)
						{
							current_triangle++;
							index_buffer[current_triangle].t[0] = index_buffer[current_triangle - 1].t[1];
							index_buffer[current_triangle].t[1] = index_buffer[current_triangle - 1].t[2];
							index_buffer[current_triangle].t[2] = q = atoi(line + i + 1) - 1;
							if (texcoord_buffer)
							{
								index_buffer[current_triangle].tx[0] = index_buffer[current_triangle - 1].tx[1];
								index_buffer[current_triangle].tx[1] = index_buffer[current_triangle - 1].tx[2];
								if (nextn)
									index_buffer[current_triangle].tx[2] = atoi(nextn + 1) - 1;
								else
									index_buffer[current_triangle].tx[2] = q;
							}
						}
					}
				}

				current_triangle++;
				break;
		}
	}

	//merge point


	tex_lookup_array = 0;
	tex_lookup_array_size = 0;
	tex_lookup_array_size_internal = 0;
	for (triangle = 0; triangle < count_triangles; triangle++)
	{
		for (wedge = 0; wedge < 3; wedge++)
		{
			for (i = 0; i < tex_lookup_array_size; i++)
			{
				if (tex_lookup_array[i].vertex_index == index_buffer[triangle].t[wedge] && tex_lookup_array[i].texture_index == index_buffer[triangle].tx[wedge])
				{
					index_buffer[triangle].tex_lookup_index[wedge] = i;
					break;
				}
			}

			if (i >= tex_lookup_array_size)
			{
				if (tex_lookup_array_size_internal <= tex_lookup_array_size)
				{
					if (tex_lookup_array_size_internal == 0)
						tex_lookup_array_size_internal = 64;
					else
						tex_lookup_array_size_internal *= 2;
					tex_lookup_array = (TexLookup*)realloc(tex_lookup_array, tex_lookup_array_size_internal * sizeof(TexLookup));
				}
				index_buffer[triangle].tex_lookup_index[wedge] = tex_lookup_array_size;
				tex_lookup_array[tex_lookup_array_size].vertex_index = index_buffer[triangle].t[wedge];
				tex_lookup_array[tex_lookup_array_size].texture_index = index_buffer[triangle].tx[wedge];
				tex_lookup_array_size++;
			}
		}
	}

	vertex_array = new Vertex[tex_lookup_array_size];
	count_vertex_array = tex_lookup_array_size;

	for (i = 0; i < tex_lookup_array_size; i++)
	{
		vertex_array[i].x = vertex_buffer[tex_lookup_array[i].vertex_index].x;
		vertex_array[i].y = vertex_buffer[tex_lookup_array[i].vertex_index].y;
		vertex_array[i].z = vertex_buffer[tex_lookup_array[i].vertex_index].z;
		if (texcoord_buffer)
		{
			vertex_array[i].tx = texcoord_buffer[tex_lookup_array[i].texture_index].x;
			vertex_array[i].ty = texcoord_buffer[tex_lookup_array[i].texture_index].y;
		}
		else
		{
			vertex_array[i].tx = 0.0;
			vertex_array[i].ty = 0.0;
		}
	}

	if (tex_lookup_array)
		free(tex_lookup_array);

	index_array = new int[count_triangles * 3];
	count_index_array = count_triangles * 3;


	i = 0;
	for (triangle = 0; triangle < count_triangles; triangle++)
	{
		for (wedge = 0; wedge < 3; wedge++)
			index_array[i++] = index_buffer[triangle].tex_lookup_index[wedge];
	}

	mkdir("cache", 0700);
	strcpy(line, "cache/");
	for (i = 0; from_file[i]; i++)
	{
		if (i && from_file[i] == '/')
		{
			line[i + 6] = 0;
			mkdir(line, 0700);
		}
		line[i + 6] = from_file[i];
	}

	snprintf(line, FILEREADER_MAX_LINE_LENGTH, "cache/%s.yfq%s", from_file, ARCH);
	i = open(line, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (i >= 0)
	{
		write(i, &count_vertex_array, 2 * sizeof(int));
		write(i, vertex_array, count_vertex_array * sizeof(Vertex));
		write(i, index_array, count_index_array * sizeof(int));
		close(i);
	}

	return true;
}

bool Model::ToMesh(Mesh* destination)
{
	Vertex* v;
	int* i;

	if (!destination->vertex_buffer.Create(GL_ARRAY_BUFFER, count_vertex_array * sizeof(Vertex)))
		return false;

	v = (Vertex*)destination->vertex_buffer.Map();
	if (!v)
		return false;

	memcpy(v, vertex_array, count_vertex_array * sizeof(Vertex));
	destination->vertex_buffer.Unmap();
	destination->count_vertices = count_vertex_array;

	if (!destination->index_buffer.Create(GL_ARRAY_BUFFER, count_index_array * sizeof(int)))
		return false;

	i = (int*)destination->index_buffer.Map();

	if (!i)
		return false;

	memcpy(i, index_array, count_index_array * sizeof(int));
	destination->index_buffer.Unmap();
	destination->count_indices = count_index_array;

	destination->max_x = max_x;
	destination->max_y = max_y;
	destination->max_z = max_z;
	destination->min_x = min_x;
	destination->min_y = min_y;
	destination->min_z = min_z;


	return true;
}
