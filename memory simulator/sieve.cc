#include <stdio.h>
#include <stdlib.h>
#include <set>

using namespace std;

// Enough space for 200 lines of output 
char output[1000][16] __attribute__ ((aligned (4096)));	

/**
* Format the contents of the given set.
* @param s The set to print.
*********************************************************************/
void print_primes(const set <int>& s)
{
	int i = 0;

	for (auto it=s.begin(); it != s.end(); ++it, ++i)
		sprintf(output[i], "%15d", *it);
}

/**
* Fill a set with integers from 2 to n and then apply the
* Sieve of Eratosthenes algorithm to remove all nonprime 
* numbers from the set.
*
* @param s The set to fill in.
* @param n The max/limit value to put into the set before the sieve.
*********************************************************************/
void sieve (set < int >& s, int n)
{
	// fill the set
	for (int i=2; i<=n; ++i)
		s.insert(i);

	// sive
	for (int i=2; i<=n; ++i)
		for (int j=i+i; j<=n; j+=i)
			s.erase(j);
}

/**
* Perform the sieve of Eratosthenes and print the prime numbers 
* from 2 to 1000 into the output array.
*********************************************************************/
int main()
{
	set <int> s;

	sieve(s, 1000);
	print_primes(s);

	return 0;
}
