/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/01/2021 at 08:30 PM
 * 
 * Chapter26_13.cc
 * Repeat the experiment in the previous exercise, but with random strings
 * of lengths in the [0:100) range.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
// #include <ctime>
#include <chrono>
using namespace std;
using distribution = std::uniform_int_distribution<unsigned>;


/**
 * Populates and then sorts a vector of a specified size, displaying the time
 * for the action to complete.
 *
 * @param vec Reference to a vector<string>
 * @param dist Reference to a uniform_int_distribution
 * @param merse Reference to a merse Random number generator
 * @param size Number of string objects to populate and sort.
 */
void sort_time(vector<string> &vec, distribution &dist,
			   std::mt19937 &merse, const int size) {
	size_t string_size;
	for (int i = 0; i < size; i++) {
		string_size = dist(merse);
		vec.emplace_back("a", string_size);
	}

	// time_t start = time(nullptr);
	auto start = chrono::system_clock::now();
	sort(vec.begin(), vec.end());
	// time_t end = time(nullptr);
	auto end = chrono::system_clock::now();

	cout << "It takes "
		 << chrono::duration_cast<chrono::seconds>(end - start).count()
		 << " second(s) to sort "
		 << size << " strings.\n";

}


int main(void) {
	const int size0 = 500000;
	const int size1 = 5000000;
	
	distribution dist{0, 100};
	std::mt19937 merse;

	vector<string> vec;
	vec.resize(size0);
	
	sort_time(vec, dist, merse, size0);

	// Now resize the array:
	vec.clear();
	vec.resize(size1);
	sort_time(vec, dist, merse, size1);
   
}

