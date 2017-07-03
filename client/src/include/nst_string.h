#ifndef __STRINGG_H
#define __STRINGG_H

 /*----------------String class-------------------*/
/*--------------v1.0-2017-06-26------------------*/

class String
{
	struct _String
	{
		char* s;
		_String(const char* c);
		~_String();
		int len;
		int ref;
	};

	_String* rep;

public:
	String(const char* c);
	String();
	String(const String& s);
	~String();
	char* NewCStr() const            { char* r = new char[rep->len + 1]; if (!r) throw; strcpy(r, rep->s); return r; };
	char* CStr() const               { return rep->s; };
	char& At(int index);
	String SubStr(int b, int e);
	int Length();
	String Trim();

	bool operator==(const String& s);
	bool operator==(const char* c);
	bool operator!=(const String& s) { return !operator==(s); };
	bool operator!=(const char* c)   { return !operator==(c); };
	char& operator[](int index)      { return At(index); };
	void operator=(const char* c);
	void operator=(const String& s);
	String operator+(const String& s);
	String operator+(const char* c);
	void operator+=(const String& s);
	void operator+=(const char* c);

	class OutOfBounds {};
};

String operator+(const char* c, const String& s);

String Trim(const String& s);

#endif //__STRINGG_H
