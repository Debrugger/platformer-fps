#include "sysinc.h"
#include "vector.h"
#include "matrix.h"

void Matrix::MultToGl()
{
	glMultMatrixd((double*)m);
}

void Matrix::Identity()
{
	memset(m, 0, sizeof(m));
	m[0][0] = 1.0;
	m[1][1] = 1.0;
	m[2][2] = 1.0;
	m[3][3] = 1.0;
}

void Matrix::SetRotation(const Vector& axis, double angle)
{
	Vector a;
	double s, c, t;

	a = axis;
	a.Normalize();
	s = sin(angle);
	c = cos(angle);
	t = 1.0 - c;

	m[0][0] = t * a.x * a.x + c;
	m[0][1] = t * a.x * a.y - s * a.z;
	m[0][2] = t * a.x * a.z + s * a.y;
	m[0][3] = 0.0;

	m[1][0] = t * a.y * a.x + s * a.z;
	m[1][1] = t * a.y * a.y + c;
	m[1][2] = t * a.y * a.z - s * a.x;
	m[1][3] = 0.0;

	m[2][0] = t * a.z * a.x - s * a.y;
	m[2][1] = t * a.z * a.y + s * a.x;
	m[2][2] = t * a.z * a.z + c;
	m[2][3] = 0.0;

	m[3][0] = 0.0;
	m[3][1] = 0.0;
	m[3][2] = 0.0;
	m[3][3] = 1.0;
}
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	Matrix ret;
	int x, y, t;


	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			ret.m[y][x] = 0.0;
			for (t = 0; t < 4; t++)
				ret.m[y][x] += m1.m[y][t] * m2.m[t][x]; 
		}
	}
	return ret;
}

Vector operator*(const Matrix& m, const Vector& v)      
{
	Vector ret;

	ret.x = m.m[0][0] * v.x + m.m[1][0] * v.x + m.m[2][0] * v.x + m.m[3][0];
	ret.y = m.m[0][1] * v.y + m.m[1][1] * v.y + m.m[2][1] * v.y + m.m[3][1];
	ret.z = m.m[0][2] * v.z + m.m[1][2] * v.z + m.m[2][2] * v.z + m.m[3][2];
	return ret;
}
