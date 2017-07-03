#include <stdio.h>
#include <string.h>
#include "nst_string.h"

String::_String::_String(const char* c)
{
	ref = 0;
	len = strlen(c);
	s = new char[len + 1];
	strcpy(s, c);
	s[len] = 0;
}

String::_String::~_String()
{
	delete s;
}

String::String()
{
	rep = 0;
}

String::String(const String& s)
{
	rep = s.rep;
	rep->ref++;
}

String::String(const char* c)
{
	rep = new _String(c);
	rep->ref++;
}

String::~String()
{
}

char& String::At(int index)
{
	if (index > rep->len || 0 > index)
		throw OutOfBounds();
	return rep->s[index];
}

String String::SubStr(int b, int e)
{                    
	if (0 > b || rep->len < e || e <= b)
		throw OutOfBounds();
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

void String::operator=(const char* c)
{
	if (rep && !strcmp(c, rep->s))
		return;
	if (rep)
	{
		if (rep->ref == 1)
			delete rep;
		else rep->ref--;
	}

	rep = new _String(c);
	rep->ref = 1;
}

void String::operator=(const String& s)
{
	if (rep == s.rep)
		return;
	rep = s.rep;
	rep->ref++;
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
	char t[rep->len + 1];
	strcpy(t, rep->s);
	t[rep->len + 1] = 0;
	char* b = t;
	while (*b <= 32)
		b++;
	char* e = t + rep->len - 1;
	while (*e <= 32)
		e--;
	*++e = 0;
	return String(b);
}
