/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/12/2021 at 02:06 PM
 * 
 * Chapter26_Drill03.cc
 * 3. Based on §26.3.1.3, complete a program that generates:
 * a. A very large sequence (what would you consider very large, and why?)
 * b. Ten sequences with a random number of elements
 * c. Ten sequences with 0, 1, 2 . . . 9 random elements (but still ordered)
 * -----------------------------------------------------------------------------
 */

#include "Chapter26_Drill.h"
#include <filesystem>
using namespace std;
using distribution = std::uniform_int_distribution<int>;


int main(void) {
	const string filename = "../Chapter26_Drill03.txt";
	
	ofstream file {"../Chapter26_Drill03.txt", ios_base::out};
	if (!file) {
		cerr << "Error: Could not open \"" << filename << "\"\n";
		exit(EXIT_FAILURE);
	}
	
	// Make large sequence:
	cout << "Creating large sequence test:\n";
	make_test(file, "test-01", 100, 0, (1 << 24));

	// Ten sequences with a random number of elements:
	distribution dist{0, 1000};

	string label;
	ostringstream os;
	
	cout << "Creating ten sequences with a random number of elements:\n";
	for (int i = 0; i < 10; i++) {
		os.str("");
		os << "test-" << i;
		make_test(file, os.str(), random_int(dist), 0, (1 << 24));		
	}
	
	// Ten sequences with 0, 1, 2 . . . 9 random elements (but still ordered)
	cout << "Creating ten sequences with 0, 1, 2, ... 9 random elements:\n";
	for (int i = 0; i < 10; i++) {
		os.str("");
		os << "test-1" << i;
		make_test(file, os.str(), i, 0, (1 << 24));
	}

}
