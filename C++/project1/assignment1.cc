/*
Programmer: 		Ibrahim Khan
Z-ID:	    		z1837663
SECTION NUMBER: 	340-0002
ASSIGNMENT NUMBER:	1
DUE DATE:		01/30/2019
*/

//preprocessor directives
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

/*declaration of global constants for size and range of arrays
data seed and search seed value for random numbers, the
number of items in each line to be displayed and the space between
*/
const int DATA_SIZE = 200;
const int DATA_RANGE = 200;
const int DATA_SEED = 9;
const int SEARCH_SEED = 17;
const int NO_ITEMS = 8;
const int ITEM_W = 4;

/*
Description:	This method takes an input vector array, a constant value 'x' to be compared with elements in the array
	and an integer value 'comparisons' to keep track of the number of comparisons before finding a match.
LOGIC:	Linear search algorithm searches for every element in the array from index 0 till the size of the array and when a match is found
	the search algorithm breaks.
*/
int linear_search(const vector<int>& inputVec, const int x, int& comparisons) {
comparisons = 0;
for(int i = 0;i < (int)inputVec.size();i++)
{
comparisons++;

        if(x == inputVec[i])
        {
                return i;
                break;
        }

}
return -1;
}
/*
Description:	This method takes an input vector array, a constant value 'x' to be compared with elements in the array
        and an integer value 'comparisons' to keep track of the number of comparisons before finding a match.
LOGIC:	The Binary search algorithm divides the whole array to compare the elements in the array with the 'x' value to be compared
	.The algorithm then checks if the value is smaller or larger than the middle and keeps dividing the array into two untill it finds a match
	if it does not find a match the algorithm returns -1 as a value.
*/
int binary_search(const vector<int>& inputVec, const int x, int& comparisons) {
int low =0;
int high = inputVec.size() - 1;
int mid;
comparisons = 0;
while(low <= high)
{
comparisons++;
mid = ((high + low)/2);
if(x == inputVec[mid])
{
return mid;

}
else if(x < inputVec[mid])
{
high = mid -1;
}
else if(x > inputVec[mid])
{
low = mid + 1;
}
}
return -1;
}
// this function prints the values in the vector array specifically 8 numbers per line with a width of 4.
void print_vec( const vector<int>& vec ){
int count =0;
for(int i =0; i < (int)vec.size(); i++)
{
cout << vec[i] << setw(ITEM_W);
count++;
if(count == NO_ITEMS)
{
count = 0;
cout << endl;
}
}
}

void average_comparisons(const vector<int>& inputVec, const vector<int>& searchVec, int (*search)(const vector<int>&, const int, int&) ) {
    int i, comparison = 0, sum = 0, found = 0;
    int res = 0;
    for (i = 0; i < (int)searchVec.size(); i++) {
        res = search( inputVec, searchVec[i], comparison );
        sum += comparison;
        if ( res >= 0 )
           found++;
    }
    cout << found << " numbers are found. The average number of comparisons in each search: " << (double)sum/(double)searchVec.size() << endl << endl;
}

int random_number() {
    return rand()%DATA_RANGE + 1;
}


int main () {

    // -------- create unique random numbers ------------------//
    vector<int> inputVec(DATA_SIZE);
    srand(DATA_SEED);
    generate(inputVec.begin(), inputVec.end(), random_number);
    sort(inputVec.begin(), inputVec.end());
    vector<int>::iterator it = unique(inputVec.begin(), inputVec.end());
    inputVec.resize( it - inputVec.begin() );
    random_shuffle( inputVec.begin(), inputVec.end() );

    cout << "------ Data source: " << inputVec.size() << " unique random numbers ------" << endl;
    print_vec(inputVec);
    cout << endl;

    // -------- create random numbers to be searched ---------//
    vector<int> searchVec(DATA_SIZE/2);
    srand(SEARCH_SEED);
    generate(searchVec.begin(), searchVec.end(), random_number);

    cout << "------ " << searchVec.size() << " random numbers to be searched: ------" << endl;
    print_vec(searchVec);
    cout << endl;

    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    sort(inputVec.begin(), inputVec.end());
    cout << "------- numbers in data source are now sorted ---------" << endl << endl;
    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    return 0;

}


