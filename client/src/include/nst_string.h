#ifndef __STRINGG_H
#define __STRINGG_H

 /*----------------String class-------------------*/
/*--------------v1.0-2017-06-26------------------*/

class String
{
	struct _String
	{
		_String(const char* c);
		~_String();
		_String* Own();
		void Assign(const char* _s);
		char* s;
		size_t len;
		int ref;
	private:
      _String(const _String&);
		_String& operator=(const _String&);
	};

	_String* rep;

public:
	String(const char* c);
	String();
	String(const String& s);
	~String();
	char* NewCStr() const            { char* r = new char[rep->len + 1]; if (!r) throw; strcpy(r, rep->s); return r; };
	char* CStr() const               { return rep->s; };
	char& At(size_t index);
	String SubStr(size_t b, size_t e);
	int Length();
	String Trim();

	operator char*() const           { return CStr(); };
	bool operator==(const String& s);
	bool operator==(const char* c);
	bool operator!=(const String& s) { return !operator==(s); };
	bool operator!=(const char* c)   { return !operator==(c); };
	char& operator[](int index)      { return At(index); };
	String& operator=(const char* c);
	String& operator=(const String& s);
	String operator+(const String& s);
	String operator+(const char* c);
	void operator+=(const String& s);
	void operator+=(const char* c);

	class OutOfBounds {};
};

String operator+(const char* c, const String& s);

String Trim(const String& s);

#endif //__STRINGG_H
