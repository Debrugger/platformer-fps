#include "sysinc.h"
#include "vector.h"
#include "matrix.h"
#include "glbuffer.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"
#include "object.h"


Object* Object::first_object = 0;
Object* Object::last_object = 0;



Object::Object()
{
	next_object = 0;
	prev_object = last_object;
	if (!first_object)
		first_object = this;
	else
		last_object->next_object = this;
	last_object = this;
	name = "unnamed";

	matrix.Identity();
}



Object::~Object()
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



void Object::Render()
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


