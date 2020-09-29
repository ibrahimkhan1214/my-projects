#Some variables needed to access private libraries for this project
HOME_DIR = /home/z1837663
INCLUDES = -I$(HOME_DIR)/include
LIB_DIR = $(HOME_DIR)/lib/

#Standard compiler variables
CC = g++
CCFLAGS = -Wall -g

#Rules start here
z1837663_project1 : z1837663_project1.o
	$(CC) -o z1837663_project1 z1837663_project1.o
z1837663_project1.o :
	$(CC) $(CCFLAGS)  -c z1837663_project1.cc
clean:
	-rm *.o z1837663_project1

