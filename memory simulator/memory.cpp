//*************************************************************
//hex.h
//CSCi 463 Assignment 3
//
//Created by ibrahim khan(z1837663)
//
//*************************************************************

//preprocessor directives
#include<cctype>
#include<iostream>
#include<string>
#include<cstdlib>
#include "memory.h"
#include "hex.h"
#include<fstream>

//calling standard library functions
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ios;

//alternate constructor 
//fills up simulated memory array with 'a5'
memory::memory(uint32_t s)
{
	s = (s+15)&0xfffffff0;
	size = s;
	mem = new uint8_t[size];

	for(uint32_t a = 0;a < size; ++a)
	{
		mem[a] = 0xa5;
	}
}

//destructor
//deletes the simulated memory array buffer
memory::~memory()
{
	delete[] mem;
}

//this methods checks if the address passed in as argument is valid to be inserted to the memory array
bool memory::check_address(uint32_t i) const
{
	if(!(i < size))
		cout << "WARNING: Address out of range: " << hex0x32(i) << endl;

	return (i<size);


}

//this method just returns the size of the simulated memory array
uint32_t memory::get_size() const
{
	return size;
}

//this method checks the validity of the passed in address 
//it will return the value return in the simulated memory array if the address is valid
uint8_t memory::get8(uint32_t addr) const
{

	if(!check_address(addr))
		return 0;

	return mem[addr];
}

//this method checks the validity of the passed in address
//it will return the value return in the simulated memory array if the address is valid
uint16_t memory::get16(uint32_t addr) const
{
	return get8(addr) | get8(addr+1)<<8;
}

//this method checks the validity of the passed in address
//it will return the value return in the simulated memory array if the address is valid
uint32_t memory::get32(uint32_t addr) const
{
	return get16(addr) | get16(addr+2)<<16;
}

////this method checks the validity of the passed in address
//it will return the value stored in the simulated memory array if the address is valid
void memory::set8(uint32_t addr, uint8_t val)
{
	if(!check_address(addr))
		return;

	mem[addr] = val;
	
}

//this method checks the validity of the passed in address
//it will return the value stored in the simulated memory array if the address is valid
void memory::set16(uint32_t addr, uint16_t val)
{
	set8(addr,val&0x0ff);
	set8(addr+1, val>>8);
}

//this method checks the validity of the passed in address
//it will return the value stored in the simulated memory array if the address is valid
void memory::set32(uint32_t addr, uint32_t val)
{
        set16(addr,val&0x0ffff);
        set16(addr+2, val>>16);
}
//this is the dump method 
//it will dump the simulated memory array
void memory::dump() const
{
	char ascii[17];	//ascii values array
	ascii[16] = 0;	//this is just to avoid any potential errors for including 17 size

	for(uint32_t i = 0; i < size; i++)
	{
        	if(i%16==0)
		{
        		if(i == 0 || i > 0 )
			{
			cout << " *" << ascii << "*" << endl;
			cout << hex32(i) << ":";
			}
		}
		uint8_t ch = get8(i);
		cout << (i%16==8?"  ":" ") << hex8(ch);
		ascii[i%16] = isprint(ch)?(ch):'.';
	}
	cout << " *" << ascii << "*" << endl;
}

//this method will check if the file opens correctly
//and read the file data in the memory array
bool memory::load_file(const string &fname)
{
	ifstream infile(fname, ios::in|ios::binary);	//declaring file
	if(!infile)  //if file fails to open show an error message and exit
	{
	        fprintf(stderr,  "\nCan't open file testdata for reading\n");
	        return false;
	}
	else
	{
		uint8_t i;		//to store the characters from file
		uint32_t Address;	//address where the characters addresses will be stored
		while(infile.read((char*)&i,1))	//reading in characters from file on byte at a time
		{
	                if(Address>=size)	//if address from file is valid
        	        {
			std::cerr<< "program too big." << endl;
			return false;
			}
			set8(Address, i);
			++Address;	//incrementing the Address counter
		}
	return true;
	}
}
