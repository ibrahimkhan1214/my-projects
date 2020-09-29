# Compiler variables
CCFLAGS = -Wall -std=c++11

# Rule to link object code files to create executable file
assignment7.exe: assignment7.o
	g++ $(CCFLAGS) -o assignment7.exe assignment7.o

# Rules to compile source code files to object code
assignment7.o: assignment7.cc
	g++ $(CCFLAGS) -c assignment7.cc

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o assignment7.exe
