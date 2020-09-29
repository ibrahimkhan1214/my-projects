
//-------------------------------------------------------------
//registerfile.cpp
//CSCI 463 Assignment 5
//
//created by Ibrahim Khan (z1837663)
//
//--------------------------------------------------------------


#include "registerfile.h"
#include "memory.h"
#include "hex.h"
#include<iostream>
#include<string>
#include<iomanip>
#include<bitset>
using namespace std;


registerfile::registerfile()
{
for(int i = 0;i < 32;i++)
{
	if(i == 0)
	{
	reg[i] = 0;
	}
	else
	{
	reg[i] = uint32_t(0xf0f0f0f0);
	}
}
}

void registerfile::dump() const
{
cout << "x0" << "   ";
for(int i = 0; i < 8;i++)
{
cout << hex32(reg[i]) << "  ";
}
cout << endl << "x8" << "   ";
for(int i = 8; i < 16;i++)
{
cout << hex32(reg[i]) << "  ";
}
cout << endl << "x16" << "  ";
for(int i = 16; i < 24;i++)
{
cout << hex32(reg[i]) << "  ";
}
cout << endl << "x24" << "  ";
for(int i = 24; i < 32;i++)
{
cout << hex32(reg[i]) << "  ";
}
}
