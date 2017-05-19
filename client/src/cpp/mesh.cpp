#include "sysinc.h"
#include "glextensions.h"
#include "glbuffer.h"
#include "mesh.h"

Mesh::Mesh()
{
	count_indices = count_vertices = 0;
}

void Mesh::Render()
{
	if (count_vertices < 3)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTexture(GL_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer.handle);
	glVertexPointer(3, GL_FLOAT, 5 * sizeof(float), (void *)0);
	glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer.handle);
	glDrawElements(GL_TRIANGLES, count_indices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
