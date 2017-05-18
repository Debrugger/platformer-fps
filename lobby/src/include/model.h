#ifndef __MODEL_H
#define __MODEL_H

struct Vertex
{
	/* position */
	union
	{
		float v[3];

		struct
		{
			float x, y, z;
		};
	};

	/* texture coords */ 
	union
	{
		float vt[2];

		struct
		{
			float tx, ty;
		};
	};
};

struct Triangle
{
	int t[3];
	int tx[3];
	int tex_lookup_index[3];
};

struct TexLookup /* hier koennen wir nachgucken ob wir einen vertex schon mit anderer texturenkoordinate geladen haben */
{
	int vertex_index;
	int texture_index;
};

class Model
{
	Vector* vertex_buffer;
	Vector2d* texcoord_buffer;
	Triangle* index_buffer;
	Vertex* vertex_array;

	int* index_array;
	int count_vertex_array;
	int count_index_array;

	public:

	Model();
	~Model();
	bool Load(const char* from_file);
	bool ToMesh(Mesh* destination);

	double width, height, depth;
	double min_x, max_x, min_y, max_y, min_z, max_z;
};

#endif //__MODEL_H
