/*
Programmer:             Ibrahim Khan
Z-ID:                   z1837663
SECTION NUMBER:         340-0002
ASSIGNMENT NUMBER:      5
DUE DATE:               03/15/2019
*/

//preprocessor directives
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "assignment5.h"

//calling standard library functions
using std::cin;
using std::cout;
using std::setw;
using std::endl;
using std::vector;
using std::iterator;

//declaring constants
const int MAX_SIZE = 40;
const int MAX_COUNT = 40;
const int WIDTH = 5;
const int ROW_SIZE = 8;

//display funtion to format the output
int mcount = 0;
int rcount = 0;
void display(int d)
{
    if ( mcount < MAX_COUNT )
    {
        cout << setw(WIDTH) << d;
        mcount++;
        rcount++;
        if ( rcount == ROW_SIZE )
	 {
            cout << endl;
            rcount = 0;
         }
    }
}

// Node class method
Node::Node(int d)
{
   data = d;
   left = NULL;
   right = NULL;
}

//binTree class methods
binTree::binTree()
{
   root = NULL;
}
void binTree::insert( int n)
{
   insert(root, n);
}
int binTree::height() const
{
   return height(root);
}
unsigned binTree::size() const{
   return size(root);
}
void binTree::inorder( void(*func)(int) )
{
   inorder(root, func);
}
void binTree::preorder( void(*func)(int) )
{
   preorder(root, func);
}
void binTree::postorder( void(*func)(int) )
{
   postorder(root, func);
}

//method insert to insert a number at a node
void binTree::insert( Node*& r, int data)
{
if(r == NULL)
{
   r = new Node(data);
}
else if(height(r->left) < height(r->right))
{
   insert(r->left, data);
}
else
{
   insert(r->right, data);
}
}

//this method gives the height of the tree
int binTree::height( Node* n) const
{
if(n == NULL)
{
   return 0;
}
else
{
   int lHeight = height(n->left);
   int rHeight = height(n->right);
if(lHeight > rHeight)
{
   return  lHeight + 1;
}
else
{
   return  rHeight + 1;
}
}
}

//this method gives the size of the tree
unsigned binTree::size( Node* n) const
{
if(n == NULL)
{
   return 0;
}
else
{
   int lSize = size(n->left);
   int rSize = size(n->right);
   return 1 + lSize + rSize;
}
}
//this method traveses the tree in order(LNR)
void binTree::inorder( Node*n, void(*func)(int) )
{
if(n == NULL)
{
   return;
}
   inorder(n->left, func);
   func(n->data);
   inorder(n->right, func);
}
//this method traverses the tree preorder (NLR)
void binTree::preorder( Node*n, void(*func)(int) )
{
if(n == NULL)
{
   return;
}
   func(n->data);
   preorder(n->left, func);
   preorder(n->right, func);
}
//this method traverses the tree postorder (LRN)
void binTree::postorder( Node*n, void(*func)(int) )
{
if(n == NULL)
{
   return;
}
   postorder(n->left, func);
   postorder(n->right, func);
   func(n->data);
}


#define BINTREE_MAIN
#ifdef BINTREE_MAIN
int main(){
    vector<int> v(MAX_SIZE);
    for (int i=1; i<MAX_SIZE; i++)
        v[i] = i;

    random_shuffle( v.begin(), v.end() );

    binTree bt;
    vector<int>::iterator it;
    for (it=v.begin(); it!=v.end(); it++)
        bt.insert( *it );

    cout << "Height: " << bt.height() << endl;
    cout << "Size: " << bt.size() << endl;
    cout << "In order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.inorder( display );
    cout << "\n\nPre order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.preorder( display );
    cout << "\n\nPost order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.postorder( display );

    cout << endl;
    return 0;
}

#endif
