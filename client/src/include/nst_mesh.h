#ifndef __MESH_H
#define __MESH_H

class Mesh 
{
	public:
		friend class Model;

		GlBuffer index_buffer;
		GlBuffer vertex_buffer;

		int count_indices;
		int count_vertices;
		double min_x, max_x, min_y, max_y, min_z, max_z;

		double GetWitdth()  {return max_x - min_x;}
		double GetHeight()  {return max_y - min_y;}
		double GetDepth()  {return max_z - min_z;}


	public:
		Mesh();
		void Render();
};

#endif //__MESH_H
