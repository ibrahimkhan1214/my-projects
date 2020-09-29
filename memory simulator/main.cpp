#include <iostream>
#include "rv32i.h"
#include "memory.h"
#include "hex.h"
#include <string>
#include <string.h>

using std::cout;
using std::endl;
using std::stoul;

int usage(int x)
{
	if(x == 1)
	cout << "Error: there should be four arguments!" << endl;
	exit(-1);

	if( x == 2)
	cout << "Error: memory file failed to load!" << endl;
	exit(-1);

}

int main(int argc,char **argv)
{
 if(argc != 4)
 usage(1);

 memory mem(stoul(argv[1],0,16));

 if (!mem.load_file(argv[3]))
 usage(2);

 rv32i sim(&mem);
 sim.run(stoul(argv[2]));
 mem.dump();

 return 0;
}
