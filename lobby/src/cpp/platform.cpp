#include "defines.h"
#include "sysinc.h"
#include "glbuffer.h"
#include "vector.h"
#include "matrix.h"
#include "texture.h"
#include "mesh.h"
#include "shader.h"
#include "object.h"
#include "platform.h"
#include "glglobals.h"
#include "playercontrols.h"

Platform* Platform::first_platform = 0;
Platform* Platform::last_platform = 0;

Platform::Platform(bool _is_circular, Mesh* m, Texture* t, double x, double y, double z)
{
	next_platform = 0;
	prev_platform = last_platform;
	if (!first_platform)
		first_platform = this;
	else
		last_platform->next_platform = this;
	last_platform = this;

	shader = &::shader;

	y_rotation = 0.0;
	gpos = y;

	MoveTo(x, y, z);

	is_circular = _is_circular;
	if (is_circular)
	{
		radius = mesh->max_x;
		if (radius < -mesh->min_x)
			radius = -mesh->min_x;

		if (radius < mesh->max_z)
			radius = mesh->max_z;

		if (radius < -mesh->min_z)
			radius = -mesh->min_z;
	}
	else
	{
		extend_x = mesh->max_x - mesh->min_x;
		extend_z = mesh->max_z - mesh->min_z;
		// TODO: falls Matrix Skalierung enthaelt, diese hier mit einberechnen!!!!!
	}
}



Platform::~Platform()
{
	if (next_platform)
		next_platform->prev_platform = prev_platform;
	else
		last_platform = prev_platform;

	if (prev_platform)
		prev_platform->next_platform = next_platform;
	else
		first_platform = next_platform;
}



void Platform::RotateY(double angle)
{
	y_rotation += angle;
	Rotate(0.0, 1.0, 0.0, y_rotation);
	if (y_rotation > 2 * M_PI);
	y_rotation -= 2 * M_PI;
}

bool Platform::Collision()
{
	double dx;
	double dz;
	Matrix reverse_m;
	Vector up, v;

	if (cam_pos.y > PosY() + mesh->max_y + PLAYER_HEIGHT)
		return false;
	if (cam_pos.y < PosY() + mesh->max_y)
		return false;

	dx = cam_pos.x - PosX();
	dz = cam_pos.z - PosZ();

	if (is_circular)
	{
		if (sqrt(dx * dx + dz * dz) > radius)
			return false;
		return true;
	}

	up.Set(0.0, 1.0, 0.0);
	reverse_m.SetRotation(up, -y_rotation);
	reverse_m.MoveTo(0.0, 0.0, 0.0);

	v.Set(cam_pos.x - PosX(), cam_pos.y - PosY(), cam_pos.z - PosZ());
	v = reverse_m  * v;

	/* not circular */
	if (v.x > extend_x * 0.5 || v.x < -extend_x * 0.5)
		return false;
	if (v.z > extend_z * 0.5 || v.z < -extend_z * 0.5)
		return false;
	return true;
}



void Platform::Land()
{
	landed_platform = this;
	cam_pos.y = PosY() + mesh->max_y + PLAYER_HEIGHT - 0.1;
}


