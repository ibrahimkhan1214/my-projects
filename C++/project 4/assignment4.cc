/*
Programmer:             Ibrahim Khan
Z-ID:                   z1837663
SECTION NUMBER:         340-0002
ASSIGNMENT NUMBER:      4
DUE DATE:               02/26/2019
*/

//preprocessor directives
#include "assignment4.h"
#include <iostream>
#include <stack>
#include <iomanip>

//declaring/calling standard methods
using std::cin;
using std::cout;
using std::setw;
using std::endl;
using std::cerr;
using std::string;

/*
this method of class Queue returns a boolean value
TRUE:	if Queue object is empty.
FALSE:	if Queue object is not empty.
*/
bool Queue::empty() const
{
	if(s1.empty() && s2.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
This method of class Queue returns the total size of both s1 and s2 stacks.
*/
int Queue::size() const
{
int x = s1.size() + s2.size();
return x;
}

/*
This method of class Queue returns the oldest element in the stack.
*/
int Queue::front()
{
//if s2 stack is empty every element of s1 is pushed into s2 which makes the
//oldest element, the last one and we can then return that by using the top() method.
	if(s2.empty())
	{
		while(!s1.empty())
		{
		s2.push(s1.top());
		s1.pop();
		}
	}
return s2.top();
}

/*
this method of class Queue returns the back of the stack which is the last
element in the stack
*/
int Queue::back()
{

//inverting the order of elements by moving the elements from stack s2 to s1
//to return the last element.
	if(s1.empty())
	{
		while(!s2.empty())
		{
		s1.push(s2.top());
		s2.pop();
		}
	}
return s1.top();
}

/*
this method of class Queue takes a value 'val' as an argument and pushes it in
s1 stack.
*/
void Queue::push(const int& val)
{
s1.push(val);
}

/*
this method of class Queue pops the last element of a stack.
*/
void Queue::pop()
{
//check if s2 stack is empty
        if(s2.empty())
        {
//moving every element of s1 to s2 stack
                while(!s1.empty())
                {
                s2.push(s1.top());
                s1.pop();
                }
        }
s2.pop();
}



int main() {
    Queue q;
    string op;
    int val = 0;
 
   cout << "operation -- size front end" << endl;
   cin >> op;
   while ( !cin.eof() ) {
        if ( op == "push" ) {
            cin >> val;
            q.push( val );
            cout << op << " " << val << "    -- ";
        }
        else if ( op == "pop" ) {
            q.pop();
            cout << op << "       -- ";
        }
        else {
            cerr << "Error input: " << op << endl;
            return 1;
        }
        if ( q.size() > 0 )
            cout << setw(3) << q.size() << setw(5) << q.front() << setw(5) << q.back() << endl;
        else
            cout << setw(3) << q.size() << endl;

        cin >> op;
    }

    while ( !q.empty() )
        q.pop();
return 0;
}
