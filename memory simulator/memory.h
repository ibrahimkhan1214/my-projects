//*************************************************************
//memory.h
//CSCi 463 Assignment 3
//
//Created by ibrahim khan(z1837663)
//
//*************************************************************

//header guards
#ifndef memory_h
#define memory_h

//preprocessor directives


//calling methods from libraries
using std::string;

//class declaration
class memory
{
public:
	memory(uint32_t siz);	//constructor
	~memory();	//destructor
	bool check_address(uint32_t i) const;	//method to check if the passed in memory address is in memory array
	uint32_t get_size() const;
	uint8_t get8(uint32_t addr) const ;
	uint16_t get16(uint32_t addr) const ;
	uint32_t get32(uint32_t addr) const ;
	void set8(uint32_t addr, uint8_t val);
	void set16(uint32_t addr, uint16_t val);
	void set32(uint32_t addr, uint32_t val);

	void dump() const;

	bool load_file(const string & fname);

private:
	uint8_t *mem; // the actual memory buffer
	uint32_t size; //size of the memory
};

//header guard close
#endif
