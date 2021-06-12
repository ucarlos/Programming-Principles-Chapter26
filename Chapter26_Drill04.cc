/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/12/2021 at 03:29 PM
 *
 * Chapter26_Drill04.cc
 * Repeat these tests for sequences of strings, such as
 * { Bohr Darwin Einstein Lavoisier Newton Turing }
 *
 * PROTIPS:
 * 1. Vector's constructor with a int argument creates an vector with n
 *    default elements rather than a vector with a max_capacity of n elements.
 *
 * 2. When using a distribution to access a vector, make sure that the
 *    distribution has the range [0, vec.size() - 1]
 *
 * 3. If an istream's state is not good(), do not call seekg to change its
 *    position.
 *
 * 4. After calling unique on a vector, remember to shrink the vector by
 *    doing vec.shrink_to_fit();
 * 5. If you become frustrated, you should step away from the computer
 *    rather than keep working on the same problem.
 * -----------------------------------------------------------------------------
 */

#include "Chapter26_Drill.h"
#include <string>
#include <list>
#include <set>
using namespace std;
using distribution = std::uniform_int_distribution<int>;

void populate_vector(vector<string> &vec, ifstream &input, int size) {
	
	if (size < 0) return;
	
	vector<string> temp_vec;
	temp_vec.reserve(size);
	int actual;
	string temp;

	for (actual = 0; actual < size && input >> temp; actual++) {
		temp_vec.push_back(temp);		
	}

	if (actual != size) {
		cerr << "Warning: Not enough words to populate list "
			 << "( " << actual << " word(s) instead of "
			 << size << " word(s))\n";
	}

	vec = std::move(temp_vec);

}

template<class Iter> void write_to_file(ostream &os, Iter first, Iter last) {
	os << "{ ";
		
	while (first != last) {
		os << *first++ << " ";
	}

	os << "}\n";
}

int main(void) {
	const string filename = "../Dictionary.txt";
	ifstream file {filename, ios_base::in};
	if (!file) {
		cerr << "Error: Could not open \"" << filename << "\"\n";
		exit(EXIT_FAILURE);
	}

	const string output_filename = "../Chapter26_Drill04.txt";
	ofstream output {output_filename, ios_base::out};
	if (!output) {
		cerr << "Error: Could not open \"" << output_filename << "\"\n";
		exit(EXIT_FAILURE);
	}
	
	
	cout << "Large SEQUENCE:\n";
	vector<string> vec;
	
	distribution dist{1, 2500};
	int random_size = random_int(dist);
	
	populate_vector(vec, file, random_size);
	
	write_to_file(output, vec.begin(), vec.end());

	// Ten sequences with a random number of elements:
	cout << "Ten sequences with a random number of elements:\n";
	for (int i = 0; i < 10; i++) {
		vec.clear();
		random_size = random_int(dist);

		file.clear();
		file.seekg(0);
		populate_vector(vec, file, random_size);
		vec.shrink_to_fit();
		random_shuffle(vec.begin(), vec.end());
		write_to_file(output, vec.begin(), vec.end());

	}


	sort(vec.begin(), vec.end());
	dist = distribution{0, static_cast<int>(vec.size() - 1)};
	// Ten sequences with 0, 1, 2 . . . 9 random elements (but still ordered)
	cout << "Ten sequences with 0, 1, 2 . . . 9 random elements (but still ordered)\n";
	set<string> s;	
	for (int i = 1; i < 10; i++) {
		s.clear();
		
		for (int j = 0; j < i; j++) {
			int i = random_int(dist);
			s.insert(vec.at(i));
		}
		
		write_to_file(output, s.begin(), s.end());		   		   	   
	}
     
}
