/*
Programmer:             Ibrahim Khan
Z-ID:                   z1837663
SECTION NUMBER:         340-0002
ASSIGNMENT NUMBER:      6
DUE DATE:               03/27/2019
*/



//header guards
#ifndef ASSIGNMENT6
#define ASSIGNMENT6
#include "assignment5.h"
//declaring BST class
class BST : public binTree {
    public:
        BST() : binTree() {}
        void insert( int );
        bool search( int );
        bool remove( int );
        int sumLeaves();
    private:
        void insert( Node*&, int );
        bool search( Node*&, int );
        bool remove( Node*&, int );
        int sumLeaves(Node*&);
};

#endif
