
/*
Programmer:             Ibrahim Khan
Z-ID:                   z1837663
SECTION NUMBER:         340-0002
ASSIGNMENT NUMBER:      2
DUE DATE:               02/06/2019
*/


//preprocessor directives
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<iomanip>
#include<iterator>
//using standard libraries
using std::cout;
using std::cin;
using std::vector;
using std::endl;
using std::setprecision;
using std::fixed;
using std::setw;
using std::showpoint;
//declarting constant variables;
const int DATA_SIZE = 100;
const int SEARCH_SIZE = 50;
const int LOW = 1;
const int HIGH = 100;
const int DATA_SEED = 11;
const int SEARCH_SEED = 7;
const int ITEM_W = 6;
const int NO_ITEMS = 10;
/*this function will generate random number of integers and assign them
to every index value of the passed in vector array.
*/
void genRndNums( vector<int>& v, int seed ) {
srand(seed);
for(unsigned int i = 0; i < v.size();i++) {
v[i] = (rand() % (HIGH - LOW + 1) + LOW);
}
}
/*
linearSearch function impliments linear search algorithm
it only function is to return true if the passed in value 'x' is found
in the passed in vector array.
*/
bool linearSearch( const vector<int>& inputVec, int x) {
auto it = find(inputVec.begin(), inputVec.end(), x);
if(it != inputVec.end())
{
return true;
}
else
{
return false;
}
}

/*
binarySearch function impliments binary search algorithm
it only function is to return true if the passed in value 'x' is found
in the passed in vector array.
*/


bool binarySearch( const vector<int>& inputVec, int x) {
if(binary_search(inputVec.begin(), inputVec.end(), x))
{
return true;
}
else
{
return false;
}
}
/*
the search algorithm uses the funtion pointer from the linearsearch and binary search
functions and looks for how many elements are present in search array that are
also in the input vector.
*/
int search( const vector<int>& inputVec, const vector<int>& searchVec,
            bool (*p)( const vector<int>&, int) ){
int comparison = 0;
for( unsigned int i = 0; i < searchVec.size(); i++)
{
if(p(inputVec,searchVec[i]))
{
comparison++;
}
}
return comparison;
}
//this function uses sort() method to sort a passed in vector array
void sortVector(vector<int>& inputVec) {
sort(inputVec.begin(), inputVec.end());
}
/*this function takes total number of successfull comparisons from search function
and divides that by passed in size of a vector array to get a percentage of
successful comparisons.
*/
void printStat (int totalSucCnt, int vec_size) {

cout << fixed << showpoint << setprecision(2);
cout << "Successful Searches: " << ((float)totalSucCnt / vec_size) * 100 << "%" << endl;
}
/*
this methods takes in a vector array and displays the elements in the array 
*/
void print_vec( const vector<int>& vec ){
int count =0;
for(int i =0; i < (int)vec.size(); i++)
{
cout << setw(ITEM_W) << vec[i];
count++;
if(count == NO_ITEMS)
{
count = 0;
cout << endl;
}
}

}

int main() {
    vector<int> inputVec(DATA_SIZE);
    vector<int> searchVec(SEARCH_SIZE);
    genRndNums(inputVec, DATA_SEED);
    genRndNums(searchVec, SEARCH_SEED);

    cout << "----- Data source: " << inputVec.size() << " randomly generated numbers ------" << endl;
    print_vec( inputVec );
    cout << "----- " << searchVec.size() << " random numbers to be searched -------" << endl;
    print_vec( searchVec );

    cout << "\nConducting linear search on unsorted data source ..." << endl;
    int linear_search_count = search( inputVec, searchVec, linearSearch );
    printStat ( linear_search_count, SEARCH_SIZE );

    cout << "\nConducting binary search on unsorted data source ..." << endl;
    int binary_search_count = search( inputVec, searchVec, binarySearch );
    printStat ( binary_search_count, SEARCH_SIZE );

    sortVector( inputVec );

    cout << "\nConducting linear search on sorted data source ..." << endl;
    linear_search_count = search( inputVec, searchVec, linearSearch );
    printStat ( linear_search_count, SEARCH_SIZE );

    cout << "\nConducting binary search on sorted data source ..." << endl;
    binary_search_count = search( inputVec, searchVec, binarySearch );
    printStat ( binary_search_count, SEARCH_SIZE );

    return 0;
}

