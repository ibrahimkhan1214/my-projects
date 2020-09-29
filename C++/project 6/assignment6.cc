/*
Programmer:             Ibrahim Khan
Z-ID:                   z1837663
SECTION NUMBER:         340-0002
ASSIGNMENT NUMBER:      6
DUE DATE:               03/27/2019
*/


//including preprocessor directives
#include <iostream>
#include "assignment5.h"
#include "assignment6.h"
//calling standard library functions
using namespace std;
int sum =0;
void BST::insert(int x)
{
    insert(root, x);
}
//inserting method for the value 'x' for BST class 
void BST::insert(Node*& n, int x)
{
    if(n == NULL)
        n = new Node(x);
    else if(x < n -> data)
        insert(n -> left, x);
    else if(x > n -> data)
        insert(n -> right, x);
}


bool BST::search(int x)
{
    return search(root, x);
}

//search method for 'x' in the BST class
bool BST::search(Node*& n, int x)
{
    if(n == NULL)
        return false;
    else if(n -> data == x)
        return true;
    else if(n -> data > x)
        return (search(n -> left, x));
    else if(n -> data < x)
        return(search(n -> right, x));
    else
        return false;
}


bool BST::remove(int x)
{
    return remove(root, x);
}
//remove method to remove a node
bool BST::remove(Node*& n, int x)
{
    Node* temp = n;
    if(n == NULL)
        return false;
    if(n -> data > x)
        return remove(n -> left, x);
    if(n -> data < x)
        return remove(n -> right, x);
    if(n -> left != NULL && n -> right != NULL)
    {
        temp = n -> left;
        while(temp -> right != NULL)
            temp = temp -> right;
        n -> data = temp -> data;
        return remove(n -> left, temp -> data);
    }
    if(n -> right == NULL)
        n = n -> left;
    else if(n -> left == NULL)
        n = n -> right;
    else
    {
        temp = n -> left;
        while(temp -> right != NULL)
            temp = temp -> right;
        temp -> right = n -> right;
        temp = n;
        n = n -> left;
        delete temp;
    }
    return true;
}


int BST::sumLeaves()
{
    return sumLeaves(root);
}

//returns a boolean value for presence of a leaf
//true if present otherwise false
bool leaf_Node(Node *root)
{
    if(root == NULL)
        return false;
    else if(root -> left == NULL && root -> right == NULL)
        return true;

    return false;
}

//calculates the total sum of leaves in the tree
int BST::sumLeaves(Node*& n)
{
if(n == NULL)
return 0;
if(n->left == NULL && n->right == NULL)
return n->data;
else
return sumLeaves(n->left) + sumLeaves(n->right);



}
