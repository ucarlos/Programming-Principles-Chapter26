/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/17/2021 at 08:26 PM
 * 
 * Binary_Search.cc
 * Sanitized it a little.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdint>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;


/**
 * Search for an item
 * @param list Reference to a vector of type T
 * @param item The item to search in the vector for
 * @return An iterator to the item if found or the end of the container otherwise.
 */
template<class T> typename std::vector<T>::iterator my_binary_search(std::vector<T> &list, T item) {
	auto new_begin = list.begin();
	auto new_end = list.end();
	auto mid = list.begin();
	
	while (new_begin <= new_end) {
		auto mid_val = std::distance(new_begin, new_end);
		mid = new_begin  + (mid_val / 2);
		
		if (*mid == item) return mid;
		else if (*mid > item)
			new_end = mid - 1;		
		else 
			new_begin = mid + 1;
		
	}
	
	return list.end(); // If not found.
}

int main(void) {
	vector<string> list;

	const string filename = "../ExampleInput.txt";
	ifstream input{filename, ios_base::in};
	if (!input) {
		cerr << "Error: Cannot open \"" << filename << "\"\n";
		exit(EXIT_FAILURE);
	}
	
	// Now populate list:
	for (string temp; input >> temp;)
		list.push_back(temp);

	
	cout << "Before sorting:\n";
	for (const string &i : list)
		cout << "\t" << i << endl;
	
	// Sort the strings and remove duplicate items.
	sort(list.begin(), list.end());
	auto it = unique(list.begin(), list.end()); 

	// Now resize the vector to fit
	list.resize(std::distance(list.begin(), it));
	
	cout << "After sorting:\n";
	for (const string &i : list)
		cout << "\t" << i << endl;
	
	//	Now search for an item
	string item = "search";
	auto iter = my_binary_search(list, item);
	if (iter == list.end())
		cout << "\"" << item << "\" could not be found in the list.\n";
	else
		cout << "\"" << item << "\" is located in index "
			 << std::distance(list.begin(), iter) << "\n";

}
