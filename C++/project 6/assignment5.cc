/*
Programmer:             Ibrahim Khan
Z-ID:                   z1837663
SECTION NUMBER:         340-0002
ASSIGNMENT NUMBER:      6
DUE DATE:               03/27/2019
*/



//header guards
#ifndef BINTREE_MAIN
#define BINTREE_MAIN

#include "assignment5.h"
#include "assignment6.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdlib>

//calling standard library functions
using namespace std;

//declaring constants
const int MAX_SIZE = 1000;
const int MAX_COUNT = 20;
const int WIDTH = 5;
const int ROW_SIZE = 5;
int mcount = 0;
int rcount = 0;

//display functions to display numbers in sorted way
void display(int d) {
    if ( mcount < MAX_COUNT ) {
        cout << setw(WIDTH) << d;
        mcount++;
        rcount++;
        if ( rcount == ROW_SIZE ) {
            cout << endl;
            rcount = 0;
        }
    }
}

binTree::binTree()
{
   root = NULL;
}

void binTree::insert(int x)
{
   insert(root, x);
}
//this methodd inserts an integer x in the node
void binTree::insert(Node*& r,int x)
{
   if(r == NULL)
   {
       r = new Node(x);
   }
   else
   {
       int left_height = size(r -> left);
       int right_height = size(r -> right);

       if(right_height < left_height)
           insert(r -> right, x);
       else
           insert(r -> left, x);
   }
}

unsigned binTree::height() const
{
   return height(root);
}

//this method calculates the height of the tree
unsigned binTree::height(Node* n) const
{
    //If n is null means tree is empty.
   if(n == NULL)
       return 0;
    else
    {
        return 1 + max(height(n->left), height (n->right));
    }
}

unsigned binTree::size() const
{
   return size(root);
}


unsigned binTree::size(Node* n) const
{
   if(n != NULL)
   {
       return 1+size(n -> left) + size( n -> right );
   }
   else
       return 0;
}

//inorder()

void binTree::inorder(void(*p)(int))
{
   inorder(root, p);
}

//method for inorder sorting of the tree
void binTree::inorder(Node* n, void(*p)(int))
{
   if(n != NULL)
   {
       inorder(n -> left, p);
       p(n -> data);

       inorder(n -> right, p);
   }
}


void binTree::preorder(void(*p)(int))
{
   preorder(root, p);
}

//method for sorting tree in preordr

void binTree::preorder(Node*n, void(*p)(int))
{
   if(n != NULL)
   {
       p (n -> data);
       preorder( n-> left, p );
       preorder( n-> right, p );
   }
}

//postorder()

void binTree::postorder(void(*p)(int))
{
   postorder(root, p);
}

//method for sorting tree in postorder
void binTree::postorder(Node* n, void(*p)(int))
{
   if(n != NULL)
   {
       postorder(n -> left, p );
       postorder(n -> right, p );
       p( n -> data );
   }
}

#endif
