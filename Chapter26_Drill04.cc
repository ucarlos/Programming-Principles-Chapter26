/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/12/2021 at 03:29 PM
 *
 * Chapter26_Drill04.cc
 * Repeat these tests for sequences of strings, such as
 * { Bohr Darwin Einstein Lavoisier Newton Turing }
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
		
	while (first != last)
		os << *first++ << " ";

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
	
	distribution dist{1, 1000};
	int random_size = random_int(dist);
	
	populate_vector(vec, file, random_size);
	
	write_to_file(output, vec.begin(), vec.end());

	// Ten sequences with a random number of elements:
	cout << "Ten sequences with a random number of elements:\n";
	for (int i = 0; i < 10; i++) {
		vec.clear();
		random_size = random_int(dist);
		

		populate_vector(vec, file, random_size);
		random_shuffle(vec.begin(), vec.end());
		write_to_file(output, vec.begin(), vec.end());
		file.seekg(0);
	}

	sort(vec.begin(), vec.end());
	unique(vec.begin(), vec.end());
	vec.shrink_to_fit();
	dist = distribution{0, (int)vec.size() - 1};

	// Ten sequences with 0, 1, 2 . . . 9 random elements (but still ordered)
	cout << "Ten sequences with 0, 1, 2 . . . 9 random elements (but still ordered)\n";
	set<string> s;	
	for (int i = 1; i < 10; i++) {
		s.clear();
		
		for (int j = 0; j < i; j++) {
			int rand = random_int(dist);
			s.insert(vec.at(rand));			
		}
		
		write_to_file(output, s.begin(), s.end());		   		   	   
	}
     
}
