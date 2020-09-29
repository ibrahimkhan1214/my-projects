//*************************************************************
//hex.cpp
//CSCi 463 Assignment 3
//
//Created by ibrahim khan(z1837663)
//
//*************************************************************

//preprocessor directives
#include "hex.h"
#include<string>
#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<bitset>
#include<string>
#include<sstream>

//calling methods from libraries
using std::string;
using std::setw;


//these methods take an unsigned integer as argument and 
//outputs a hex number.
std::string hex8(uint8_t i)
{
	std::ostringstream os;
	os << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint16_t>(i);
	return os.str();

}

std::string hex32(uint32_t i)
{
	std::ostringstream os;
	os << std::hex << std::setfill('0') << std::setw(8) << i;
	return os.str();
}

std::string hex0x32(uint32_t i)
{
	return std::string("0x")+hex32(i);
}



