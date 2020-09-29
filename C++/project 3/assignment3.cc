/*
Programmer:             Ibrahim Khan
Z-ID:                   z1837663
SECTION NUMBER:         340-0002
ASSIGNMENT NUMBER:      3
DUE DATE:               02/15/2019
*/


//preprocessor directives
#include<iostream>
#include<cctype>
#include<set>
#include<string>
#include<iomanip>
#include<algorithm>


//declaring constants
const int NO_ITEMS=6;
const int ITEM_W=4;


//calling specific library methods
using std::cout;
using std::cin;
using std::endl;
using std::set;
using std::setw;
using std::string;


/*
this is the sieve function that takes a set as an argument a const integer value for lower bound and one for upper bound
it is responsible for making sure the set is empty and then it is ready to be filled with integer values as provided
in the arguments. it then impliments the sieve algorithm to filter out the numbers between prime numbers which in
the end are left in the set.
*/
void sieve( set<int>& s, const int lower, const int upper)
{
    s.clear();
    for(int i=lower;i<=upper;i++)
	{
        s.insert(i);
	}
    for(int outer=2;(outer)*(outer)<upper;outer++)
        {
	for(int inner=(outer)*2;inner<=upper;inner+=outer)
	{
            s.erase(inner);
	}
	}
}


/*
this function prints the prime numbers in the set 's' passed in as argument from lower bound untill upper bound
*/
void print_primes( const set<int>& s, const int lower, const int upper)
{
int counter = 0;

    cout << endl;

    cout << "There are " << s.size()<<" prime numbers between "<<lower<<" and "<<upper<<":"<<endl;
	auto it = s.begin();
    for( it = s.begin();it != s.end();it++)
	{
cout << setw(ITEM_W) << *it;

counter++;

if ( counter == NO_ITEMS)
{
cout << endl;
counter = 0;
}
	}

    cout << endl << endl;

}



/*
this function takes the set 's' as argument and prompts the user for inputs for lower and upper bounds and also if the user wants to continue the game 
or not after each iteration of the game.
*/
void run_game(set<int>& s)
{
    int lower,upper;
    string answer;
    do
    {
        do
        {
            lower = 0;
	    upper = 0;
            cout<<"Please input lower bound and upper bound and hit enter (e.g. 10 100):"<<endl;
            cin>>lower;
            cin>>upper;
            cin.clear();
            cin.ignore(256,'\n');
		if(lower < 2)
		{
		  lower = 2;
		}
        }while(lower >= upper);

        sieve(s,lower,upper);

        print_primes(s,lower,upper);

        do
        {
            cout << "Do you want to continue or not? Please answer yes or no and hit enter:" << endl;
            cin >> answer;

            for(unsigned int i=0;i<answer.length();++i)
		{
                answer[i]=tolower(answer[i]);
		}
        }while(answer!="no" && answer!="yes");
    }while(answer=="yes");
}


int main() {
    set<int> s;
    run_game(s);
    return 0;
}

