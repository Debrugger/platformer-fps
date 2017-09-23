#include "sysinc.h"
#include "nst_vector.h"
#include "nst_matrix.h"
#include "nst_glbuffer.h"
#include "nst_shader.h"
#include "nst_texture.h"
#include "nst_mesh.h"
#include "nst_mapdata.h"

MapData::MapObject::MapObject()
{
	next_object = 0;
	prev_object = last_object;
	if (!first_object)
		first_object = this;
	else
		last_object->next_object = this;
	last_object = this;

	matrix.Identity();
}

MapData::MapObject::~MapObject()
{
	if (next_object)
		next_object->prev_object = prev_object;
	else
		last_object = prev_object;

	if (prev_object)
		prev_object->next_object = next_object;
	else
		first_object = next_object;
}

void MapData::MapObject::Render()
{
	if (!mesh)
		return;

	glPushMatrix();
	matrix.MultToGl();

	if (shader)
		shader->Use();
	else
		Shader::UseNone();
	if (texture)
		texture->Use();
	else
		Texture::UseNone();

	mesh->Render();
	glPopMatrix();
}

void Object::Rotate(const Vector& axis, double angle)
{
	Vector pos;
	Matrix rot;

	pos = GetPos();
	MoveTo(0.0, 0.0, 0.0);

	rot.SetRotation(axis, angle);
	matrix = matrix * rot;

	MoveTo(pos);
}
