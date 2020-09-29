//-------------------------------------------------------------
//registerfile.h
//CSCI 463 Assignment 5
//
//created by Ibrahim Khan (z1837663)
//
//--------------------------------------------------------------

#ifndef registerfile_h
#define registerfile_h


#include<iostream>
#include<iomanip>
#include<string>
#include<cassert>
#include<stdint.h>

using std::cout;
using std::cin;
using std::endl;

class registerfile
{
private:
	int32_t reg[32];

public:
	registerfile();

	void set(uint32_t r, int32_t val)
	{
	assert(r<32 && "illegal register number");
	if(r != 0)
	{
	reg[r] = val;
	}
	}

	int32_t get(uint32_t r) const
	{
	assert(r<32 && "illegal register number");
	return reg[r];
	}
	void dump() const;
};


#endif
