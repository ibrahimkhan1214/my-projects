/*
Programmer:             Ibrahim Khan
Z-ID:                   z1837663
SECTION NUMBER:         340-0002
ASSIGNMENT NUMBER:      7
DUE DATE:               04/03/2019
*/

//Preprocessor directives
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

/*
Prototype functions
*/
void build_heap(vector<int>& v, int heap_size, bool (*compar)(int, int));
void heapify(vector<int>& v, int heap_size, int r, bool (*compar)(int, int));
bool less_than(int e1, int e2);
bool greater_than(int e1, int e2);
void heap_sort(vector<int>& v, int heap_size, bool (*compar)(int, int));
int extract_heap(vector<int>& v, int& heap_size, bool (*compar) (int, int));
void print_vector (vector <int>& v, int pos, int size);

//Declaring constants
const int HEAP_SIZE = 50;
const int SET_WIDTH = 5;
const int SET_LENGTH = 8;

//Main function
int main(int argc, char** argv) {
    // ------- creating input vector --------------
    vector<int> v;
    v.push_back(-1000000);    // first element is fake
    for (int i=1; i<=HEAP_SIZE; i++)
        v.push_back( i );
    random_shuffle( v.begin()+1, v.begin()+HEAP_SIZE+1 );

    cout << "\nCurrent input numbers: " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing min heap ------------------
    cout << "\nBuilding a min heap..." << endl;
    build_heap(v, HEAP_SIZE, less_than);
    cout << "Min heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, less_than);
    cout << "Heap sort result (in ascending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing max heap ------------------
    cout << "\nBuilding a max heap..." << endl;
    build_heap(v, HEAP_SIZE, greater_than);
    cout << "Max heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, greater_than);
    cout << "Heap sort result (in descending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    return 0;
}
// Function Definitions

/*************************************************************************

The functionality of this method is to create a heap.
This is a void method so it will not have any return value.

**************************************************************************/
void build_heap(vector<int>& v, int heap_size, bool (*compar)(int, int))
{

for(int i = heap_size/2; i >= 1; i--)
{
    heapify(v, heap_size, i, compar);
}

}
/*************************************************************************

This method is of void data type
and its functionality is to use it to  heapify.

**************************************************************************/
void heapify(vector<int>& v, int heap_size, int r, bool (*compar)(int, int))
{
	int left = 2 * r;
	int right = 2 * r + 1;
	int largest;
	int temp;

   if(left <= heap_size && compar(v[left], v[r]))
   {
      largest = left;
   }
   else
   {
      largest = r;
   }

   if(right <= heap_size && compar(v[right], v[largest]))
   {
      largest = right;
   }

   if(largest != r)
   {
      temp = v[r];
      v[r] = v[largest];
      v[largest] = temp;
      heapify(v, heap_size, largest, compar);
   }

}

/******************************************************************************

This function compares two integers and returns True if the integer at e1
argument is less than the integer at e2 argument otherwise it returns False

*******************************************************************************/
bool less_than(int e1, int e2)
{
   if(e1 < e2)
   {
       return true;
   }
   else
   {
       return false;
   }
}

/********************************************************************************

This function compares two integers and returns True if the integer at e1
argument is greater than the integer at e2 argument otherwise it returns False

**********************************************************************************/
bool greater_than(int e1, int e2)
{
   if(e1 > e2)
   {
      return true;
   }
   else
   {
      return false;
   }
}
/*************************************************************************

This method sorths the heap

**************************************************************************/

void heap_sort(vector<int>& v, int heap_size, bool (*compar)(int, int))
{

   int i;

   for(i = heap_size; i >= 2; i--)
   {
       v[i] = extract_heap(v, heap_size, compar);
   }

   reverse(v.begin() + 1, v.end());

}
/*************************************************************************

This method extracts the root of a heap in v

**************************************************************************/
int extract_heap(vector<int>& v, int& heap_size, bool (*compar) (int, int))
{
   int extract;

   if(heap_size < 1)
   {
      cout << "Error" << endl;
   }
   extract = v[1];

   v[1] = v[heap_size];

   heap_size = heap_size - 1;

   heapify(v, heap_size, 1, compar);

   return extract;
}
/*************************************************************************

The functionality of this method is to print the elements in vector 'v'
such that only 8 numbers get printed on each line with a width of 4 spaces
between them.

**************************************************************************/
void print_vector (vector <int>& v, int pos, int size)
{
   for(; pos <= size; pos++)
   {
      cout << setw(SET_WIDTH) << v[pos] << " ";
      if((pos % SET_LENGTH) == 0)
      {
         cout << endl;
      }
    }

   cout << endl;
}
