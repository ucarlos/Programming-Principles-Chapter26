/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/13/2021 at 01:04 AM
 * 
 * Chapter26_01.cc
 * Run your binary search algorithm from §26.1 with the tests presented in
 * §26.3.2.1.
 * -----------------------------------------------------------------------------
 */

#include "SimpleBinarySearch.h"
#include "Chapter26_Drill.h"
using namespace std;

string print_sequence(vector<int> &vec) {
	ostringstream os;
	os << "{ ";
	for (const int &i : vec)
		os << i << " ";
	os << "}";

	return os.str();
}

int main(void) {
	const string filename = "../Chapter26_Drill01.txt";
	ifstream file{filename, ios_base::in};

	if (!file) {
		cerr << "Can't open \"" << filename << "\"!\n";
		exit(EXIT_FAILURE);
	}

	Test test;
	cout << boolalpha;
	while (file.good()) {
		file >> test;
		
		if (test.label == "empty-string")
			continue;
		
		int result = simple_binary_search(test.seq, test.expected);
		if (result == -1)
			cout << "Could not find " << test.expected << " in ";
		else
			cout << "Found " << test.expected << " in ";
		
		cout << print_sequence(test.seq) << "\n(Test result: " << test.result << ")\n\n";

	}

}

