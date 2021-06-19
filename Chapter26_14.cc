/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/19/2021 at 04:19 PM
 * 
 * Chapter26_14.cc
 * Repeat the previous exercise, except using a map rather than a vector so
 * that we don’t need to sort.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <set>
#include <string>
#include <random>
#include <chrono>

using namespace std;
using distribution = uniform_int_distribution<>;


/**
 * Populates a set of string with a given size and displays the time for the
 * action to complete.
 * @param s
 * @param dist
 * @param merse
 * @param size
 */
void sort_time(set<string> &s, distribution &dist, std::mt19937 &merse, const int size) {
	vector<char> vc;
	vc.reserve(26);
for (int i = 0; i < 26; i++)
		vc.push_back('a' + i);

	distribution letter_dist{0, static_cast<int>(vc.size()) - 1};

	// Now populate the set:
	auto start = chrono::system_clock::now();
	
	
	char temp;
	int temp_length;
	for (int i = 0; i < size; i++) {
		temp = vc.at(letter_dist(merse));
		temp_length = dist(merse);
		s.insert(string(temp, temp_length));
	}	
	auto end = chrono::system_clock::now();


	cout << "It took "
		 << chrono::duration_cast<chrono::seconds>(end - start).count()
		 << " seconds to insert into a string set of size "
		 << size
		 << ".\n";
}


int main() {

	const int size1 = 500000;
	const int size2 = 5000000;
	const int size3 = 50000000;
	distribution dist {0, 100};
	std::mt19937 merse;
	
	set<string> s;
	sort_time(s, dist, merse, size1);

	s.clear();
	sort_time(s, dist, merse, size2);
	
	s.clear();
	sort_time(s, dist, merse, size3);
}
