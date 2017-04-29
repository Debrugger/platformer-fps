#ifndef __OBJECT_H
#define __OBJECT_H

class Object
{
	static Object* first_object;
	static Object* last_object;
	Object* next_object;
	Object* prev_object;


	public:
	Object();
	~Object();

	Mesh* mesh;
	Shader* shader;
	Texture* texture;
	Matrix matrix;
	const char *name;

	static Object* FirstObject()   { return first_object; };
	static Object* LastObject()    { return last_object;  };
	Object* PrevObject()           { return prev_object;  };
	Object* NextObject()           { return next_object;  };

	void Render();

	Vector GetPos()                                                          { Vector ret; ret.x = matrix.m[3][0]; ret.y = matrix.m[3][1]; ret.z = matrix.m[3][2]; return ret; };
	void Move(double x, double y, double z)                                  { matrix.m[3][0] += x; matrix.m[3][1] += y; matrix.m[3][2] += z; };
	void Move(const Vector& v)                                               { matrix.m[3][0] += v.x; matrix.m[3][1] += v.y; matrix.m[3][2] += v.z; };
	void MoveTo(double x, double y, double z)                                { matrix.m[3][0] = x; matrix.m[3][1] = y; matrix.m[3][2] = z; };
	void MoveTo(const Vector& v)                                             { matrix.m[3][0] = v.x; matrix.m[3][1] = v.y; matrix.m[3][2] = v.z; };

	void Rotate(double x_axis, double y_axis, double z_axis, double angle)   { Vector v; v.x = x_axis; v.y = y_axis; v.z = z_axis; Rotate(v, angle); };

	void Rotate(const Vector& axis, double angle);
	double PosX()                                                            { return matrix.PosX(); };
	double PosY()                                                            { return matrix.PosY(); };
	double PosZ()                                                            { return matrix.PosZ(); };
	void PosX(double x)                                                      { matrix.PosX(x); };
	void PosY(double y)                                                      { matrix.PosX(y); };
	void PosZ(double z)                                                      { matrix.PosX(z); };
};

#endif // __OBJECT_H

