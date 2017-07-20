#include <stdio.h>
#include <string.h>
#include "nst_string.h"

String::_String::_String(const char* c)
{
	ref = 1;
	len = strlen(c);
	s = new char[len + 1];
	strcpy(s, c);
	s[len] = 0;
}

String::_String::~_String()
{
	delete[] s;
}

String::_String* String::_String::Own()
{
	if (ref == 1)
		return this;
	ref--;
	return new _String(s);
}

void String::_String::Assign(const char* _s)
{
	size_t nlen = strlen(_s);
	if (len != nlen)
	{
		delete[] s;
		len = nlen;
		s = new char[len + 1];
	}
	strcpy(s, _s);
}

String::String()
{
	rep = new _String("");
}

String::String(const String& s)
{
	rep = s.rep;
	rep->ref++;
}

String::String(const char* c)
{
	rep = new _String(c);
}

String::~String()
{
	if (--rep->ref == 0)
		delete rep;
}

char& String::At(size_t index)
{
	if (index > rep->len)
		throw OutOfBounds();
	return rep->s[index];
}

String String::SubStr(size_t b, size_t e)
{                    
	if (0 > b || rep->len < e || e <= b)
		return "";
		//throw OutOfBounds();
	char t[rep->len + 1];
	strcpy(t, rep->s);
	t[e + 1] = 0;
	char r[e - b + 1];
	r[e - b + 1] = 0;
	strcpy(r, t + b);
	return String(r);
}

int String::Length()
{
	return strlen(CStr());
}

String& String::operator=(const char* c)
{
	if (rep->ref == 1)
	{
		rep->Assign(c);
	}
	else
	{
		rep->ref--;
		rep = new _String(c);
	}
	return *this;
}

String& String::operator=(const String& s)
{
	if (rep == s.rep)
		return *this;
	if (--rep->ref == 0)
		delete rep;
	rep = s.rep;
	rep->ref++;
	return *this;
}

bool String::operator==(const String& s)
{
	return !strcmp(CStr(), s.CStr());
}

bool String::operator==(const char* c)
{
	return !strcmp(CStr(), c);
}

String String::operator+(const String& s)
{
	return operator+(s.CStr());
}

String String::operator+(const char* c)
{
	int l = strlen(c);
	char con[rep->len + l + 1];
	strcpy(con, CStr());
	strcpy(con + rep->len, c);
	con[rep->len + l + 1] = 0;
	return String(con);
}

void String::operator+=(const String& s)
{
	String con = operator+(s);
	operator=(con);
}

void String::operator+=(const char* s)
{
   String con = operator+(s);
	operator=(con);
}

String operator+(const char* c, const String& s)
{
	return String(c) + s;
}

String String::Trim()
{
	//char t[rep->len + 1];
	//strcpy(t, rep->s);
	//t[rep->len + 1] = 0;
	//char* b = t;
	//while (*b <= 32)
	//	b++;
	//char* e = t + rep->len - 1;
	//while (*e <= 32)
	//	e--;
	//*++e = 0;
	//return String(b);
	
	char tmp[rep->len + 1];
   strcpy(tmp, rep->s);
	char* b = tmp;
	while (rep->len > (size_t)(b - tmp) && *b <= 32)
		b++;
	char* e = tmp + rep->len;
	while (e != b && *(e - 1) <= 32)
		e--;
	*e = 0;
	return String(b);
}
