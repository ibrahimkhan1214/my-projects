# Compiler variables
CCFLAGS = -Wall -std=c++11

# Rule to link object code files to create executable file
assignment4.exe: assignment4.o
	g++ $(CCFLAGS) -o assignment4.exe assignment4.o

# Rules to compile source code files to object code
assignment4.o: assignment4.cc
	g++ $(CCFLAGS) -c assignment4.cc

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o assignment4.exe

