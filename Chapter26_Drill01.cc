/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/10/2021 at 10:02 PM
 * 
 * Chapter26_Drill01.cc
 * Implement the input operator for Test from §26.3.2.2.
 * -----------------------------------------------------------------------------
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <sstream>
using namespace std;


struct Test {
	string label{};
	int val{};
	vector<int> seq;
	bool result{};

};



/**
 *
 * @param is Reference to an istream object
 * @param t Reference to an Test objects
 * @returns A Reference to a the istream object parameter.
 */
istream& operator>>(istream &is, Test &t) {
	
	const static string pattern = R"(\{\s*[^\s]+\s*\-?\d+\s*\{(\s*\-?\d+)*\s*\}\s*[0-1]\s*\})";
	
	const regex expression{pattern};

	static string line;
	getline(is, line);

	if (!regex_match(line, expression)) {
		static ostringstream os;
		os << "Error: \"" << line << "\" Does not match the regex \""
		   << pattern << "\"" << endl;
		throw runtime_error(os.str());
	}

	// Probably should use a regex search and match but fuck it
	static istringstream iss;
	iss.str(line);
	
	iss.ignore(256, '{');

	string label{};
	iss >> label;
	
	int search_val{};
	iss >> search_val;

	iss.ignore(256, '{');

	vector<int> temp_vec;
	for (int temp; iss >> temp;)
		temp_vec.push_back(temp);

	// Now check iss state
	if (iss.bad()) // 
		throw runtime_error("Error: istringstream is in bad state!");

	// if (iss.eof()) // Only if you modify the file while reading or something
	// 	throw runtime_error("Error: istringstream did not expect eof.");
	
	if (iss.fail())
		iss.clear();


	iss.ignore(256, '}');

	static bool result;
	iss >> result;

	// Now assign:
	t.label = label;
	t.val = search_val;
	t.result = result;
	t.seq = std::move(temp_vec);
      	
	return is;
}



int main(void) {
	const string filename = "../Chapter26_01.txt";
	ifstream file{filename, ios_base::in};

	if (!file) {
		cerr << "Error: Could not open \"" << filename << "\"\n";
		exit(EXIT_FAILURE);
	}


	Test example;
	istringstream is;
	string temp;
	for (; file.good();) {
		file >> example;

		cout << "Contents of Test \"" << example.label << "\"\n";
		cout << "Label: " << example.label << endl;
		cout << "Test value: " << example.val << endl;
		cout << "List:\n";
		for (const int &i : example.seq)
			cout << "\t" << i << endl;
		cout << "Expecting: " << example.result << endl << endl;

	}

}

