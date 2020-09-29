/*
NAME:		IBRAHIM KHAN
CLASS:		CSCI 340
DUE DATE:	04/19/2019
ASSIGNMENT:	8
*/

//preprocessor directives
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "assignment8.h"
//calling std library methods
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::setw;
using std::ios;
using std::right;
using std::vector;
/*******************************************************************************

This take a line of input and parse it to make a new entry.

*******************************************************************************/
Entry* get_entry(const string& line)
{
	Entry* parsed_line = new Entry;

	parsed_line->key = line.substr(2, 3);
	parsed_line->description = line.substr(6, line.length() - 6);
	return parsed_line;
}

/*******************************************************************************

This method takes input and return the item key.

*******************************************************************************/
string get_key(const string& line)
{
	string gKey = line.substr(2, 3);
	return gKey;
}

/*******************************************************************************

This is a default constructor. The hash table which is a vector of entry,

*******************************************************************************/
HT::HT(int s = 11)
{
	hTable = new vector<Entry>(s);
	table_size = s;
	item_count = 0;
}

/*******************************************************************************

THis is the destructor for Hash Table.

*******************************************************************************/
HT::~HT()
{
	delete hTable;
}

/*******************************************************************************

It is the public function that searches the hash table for a record with
the given key. It computes the hash value. If the search was successful
the function will return the position of the found element.

*******************************************************************************/
int HT::search(const string& key)
{
	int keyIndex = hashing(key);
	for (int i = 0; i < table_size; i++) {
		if ((*hTable)[keyIndex].key == key)
			return keyIndex;
		keyIndex = (keyIndex + 1) % table_size;
	}
	return -1;
}

/*******************************************************************************

Uses : It is public member function to inserts item e in the hash table. It first
checks if the items key already exists in the hash table by calling the
search() function. If the key exists, an error message is printed and insert()
returns false. If the hash table is already full, an error message is printed
and the function returns false. If the above checks do not fail, the hash value
is computed for the key of e. If the hash table position of the hash value is
empty, the item is placed on that position. Otherwise, an appropriate position
is determined by linear probing. After the item is inserted, item_count is
increased and the function returns true.

*******************************************************************************/
bool HT::insert(const Entry& e)
{
	int keyIndex = hashing(e.key);

	string sKey = e.key;
	if (search(sKey) != -1) {
		cerr << "Unable to insert - identical key found" << endl;
		return false;
	}
	else if (item_count == table_size) {
		cerr << "Unable to insert - the table is full." << endl;
		return false;
	}

	else {
		int i;
		for (i = 0; i < table_size; i++) {
			if ((*hTable)[keyIndex].key == "---" || (*hTable)[keyIndex].key == "+++") {
				(*hTable)[keyIndex] = e;
				item_count++;

				return true;
			}
			keyIndex = keyIndex + 1 % table_size;
		}
	}
	return false;
}

/*******************************************************************************

It is public member function for remove it simply removes an item with
the given key value.

*******************************************************************************/
bool HT::remove(const string& s)
{
	if (search(s) == -1) {
		return false;
	}

	else {
		int keyIndex = search(s);

		(*hTable)[keyIndex].key = "+++";
		item_count--;
		return true;
	}
}

/*******************************************************************************

It is public member function for printing the existing entries in the
hash table. It prints the index value, key and description.


*******************************************************************************/
void HT::print()
{
	cout << endl << "----Hash Table-----" << endl;

	for (int i = 0; i < table_size; i++) {
		if ((*hTable)[i].key != "---" && (*hTable)[i].key != "+++") {
			cout << right << setw(2) << i << ": ";
			cout << (*hTable)[i].key << " ";
			cout << (*hTable)[i].description << endl;
		}
	}
	cout << "---------------------------" << endl << endl;
}



int HT::hashing(const string& key) {
	return ((int)key[0] + (int)key[1] + (int)key[2]) % table_size;
}

int main(int argc, char** argv) {
	if (argc < 2)
	{
	cerr << "argument: file-name\n";
	return 1;
	}
	HT ht;
	ifstream infile("assignment8input.txt", ios::in);
	string line;
	infile >> line;
	while (!infile.eof()) {
		if (line[0] == 'A') {
			Entry* e = get_entry(line);
			ht.insert(*e);
			delete e;
		}
		else {
			string key = get_key(line);
			if (line[0] == 'D') {
				cout << "Removing " << key << "...\n";
				bool removed = ht.remove(key);
				if (removed)
					cout << key << " is removed successfully...\n\n";
				else
					cout << key << " does not exist, no key is removed...\n\n";
			}
			else if (line[0] == 'S') {
				int found = ht.search(key);
				if (found < 0)
					cout << key << " does not exit in the hash table ..." << endl << endl;
				else
					cout << key << " is found at table position " << found << endl << endl;
			}
			else if (line[0] == 'P') {
				cout << "\nDisplaying the table: " << endl;
				ht.print();
			}
			else
				cerr << "wrong input: " << line << endl;
		}
		infile >> line;

	}

	infile.close();
	return 0;
}
