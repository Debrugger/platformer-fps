#ifndef __VECTOR_H
#define __VECTOR_H
#define EPSILON 0.0001

struct Vector2d
{
	union
	{
		double v[2];
		struct
		{
			double x, y;
		};
	};

	void Set(double _x, double _y)                   { x  = _x; y = _y;};
};

struct Vector
{
	union
	{
		double v[3];
		struct
		{
			double x, y, z;
		};
	};

	void Set(double _x, double _y, double _z)                   { x  = _x; y = _y; z= _z; };
	void Add(double _x, double _y, double _z)                   { x  += _x; y += _y; z += _z; };

	double SquaredLen()                                         { return (x*x + y*y + z*z); };
	double Len()                                                { return sqrt(x*x + y*y + z*z); };

	void Normalize()                                            { operator*=(1.0 / Len()); };

	bool IsEqual(const Vector &other)                           { if ((fabs(x - other.x)) < EPSILON && (fabs(y - other.y)) < EPSILON && (fabs(z - other.z)) < EPSILON) return true; return false;};

	Vector &operator =(const Vector &other)                     { x  = other.x; y = other.y; z = other.z; return *this; };
	Vector &operator +=(const Vector &other)                    { x  += other.x; y += other.y; z += other.z; return *this; };
	Vector &operator -=(const Vector &other)                    { x  -= other.x; y -= other.y; z -= other.z; return *this; };
	Vector &operator *=(const Vector &other)                    { x *= other.x; y *= other.y; z *= other.z; return *this; };
	Vector &operator *=(double scalar)                          { x *= scalar; y *= scalar; z *= scalar; return *this; };

};

inline Vector operator +(const Vector &v1, const Vector &v2)    { Vector r; r.x = v1.x + v2.x; r.y = v1.y + v2.y; r.z = v1.z + v2.z; return r; };
inline Vector operator -(const Vector &v1, const Vector &v2)    { Vector r; r.x = v1.x - v2.x; r.y = v1.y - v2.y; r.z = v1.z - v2.z; return r; };
inline Vector operator *(const Vector &v1, const Vector &v2)    { Vector r; r.x = v1.x * v2.x; r.y = v1.y * v2.y; r.z = v1.z * v2.z; return r; };
inline Vector operator *(const Vector &v, double scalar)                       { Vector r; r.x = v.x * scalar; r.y = v.y * scalar; r.z = v.z * scalar; return r; };

inline double Dot(const Vector &v1, const Vector &v2)           { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; };
inline Vector Cross(const Vector &v1, const Vector &v2)         { Vector r; r.x = v1.y * v2.z - v1.z * v2.y; r.y = v1.z * v2.x -v1.x * v2.z; r.z = v1.x * v2.y -v1.y * v2.x; return r; };

#endif // __VECTOR_H
