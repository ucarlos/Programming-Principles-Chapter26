/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 05/30/2021 at 11:51 PM
 * 
 * Simple_Binary_Search.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
using namespace std;

template<class T> size_t simple_binary_search(vector<T> vec, T item) {
	int begin = 0;
	int end = vec.size() - 1;

	while (begin <= end) {
		int mid = (begin + end) / 2;
		T result = vec.at(mid);
		if (result == item)
			return mid;
		else if (result < item)
			begin = mid + 1;
		else
			end = mid - 1;
	}

	return -1; 	// Otherwise, return -1 if not found:

}


int main(void) {
	vector<int> vecd;
	for (int i = 0; i < 100; i++)
		vecd.push_back(i);



	
	int val;
	cout << "Enter a value: ";
	cin >> val;
	
	size_t result = simple_binary_search(vecd, val);
	bool found = (result != -1);
	cout << "Is value in the vector? ";
	if (found)
		cout << "Yes, at index " << result << endl;
	else cout << "No.\n";

   
}

