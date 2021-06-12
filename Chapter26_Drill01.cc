/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/10/2021 at 10:02 PM
 * 
 * Chapter26_Drill01.cc
 * Implement the input operator for Test from §26.3.2.2.
 * -----------------------------------------------------------------------------
 */

#include "Chapter26_Drill.h"
using namespace std;

int main(void) {
	// const string filename = "../Chapter26_Drill01.txt";
	// const string filename = "../Chapter26_Drill02.txt";
	const string filename = "../Chapter26_Drill03.txt";
	ifstream file{filename, ios_base::in};

	if (!file) {
		cerr << "Error: Could not open \"" << filename << "\"\n";
		exit(EXIT_FAILURE);
	}

	Test example;
	istringstream is;
	string temp;

	cout << boolalpha;
	for (; file.good();) {
		file >> example;

		cout << "Contents of Test \"" << example.label << "\"\n";
		cout << "Label: " << example.label << endl;
		cout << "Test value: " << example.val << endl;
		cout << "List:\n";
		for (const int &i : example.seq)
			cout << "\t" << i << endl;
		cout << "Expected result: " << example.result << endl << endl;

	}


}

