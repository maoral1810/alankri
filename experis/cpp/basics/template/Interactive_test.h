#ifndef X_H
#define X_H

#include <iostream>
using namespace std;

class String_t {
public:
	void Prepend(const char* str)	{ cout << "-----> String_t::Prepend()" << endl;}
	void Compare(const String_t &)	{ cout << "-----> String_tX::Compare()" << endl;}
	const char* GetString() 		{ cout << "-----> String_t::getString()" << endl;}
};

#endif
