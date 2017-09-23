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


	static Object* FirstObject()   { return first_object; };
	static Object* LastObject()    { return last_object;  };
	Object* PrevObject()           { return prev_object;  };
	Object* NextObject()           { return next_object;  };

	void Render();

	};

#endif // __OBJECT_H

