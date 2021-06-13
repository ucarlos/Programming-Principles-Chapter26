/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/13/2021 at 01:51 PM
 * 
 * Chapter26_02.cc
 * Modify the testing of binary_search to deal with arbitrary element types.
 * Then, test it with string sequences and floating-point sequences.
 * -----------------------------------------------------------------------------
 */

#include "SimpleBinarySearch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <random>
#include <fstream>
#include <sstream>
using namespace std;

template <class T> struct Test {
	std::string label{};
	T expected{};
	std::vector<T> seq;
	bool result{};
};


template<class T>istream& operator>>(istream &is, Test<T> &test) {
	const static string pattern = R"(\{\s*[^\s]+\s*[^\s]+\s*\d+\s*\{(\s*[^\s]+)*\s*\}\s*[0-1]\s*\})";

	const regex expression{pattern};
	
	static string line;
	getline(is, line);

	if (line.empty()) { // Handle empty line
		test.label = "empty-string";
		test.expected = T{};
		test.result = false;
		test.seq = vector<T>{};
		return is;
	}

	
	if (!regex_match(line, expression)) {
		static ostringstream os;
		os << "Error: \"" << line << "\" Does not match the regex \""
		   << pattern << "\"" << endl;
		throw runtime_error(os.str());
	}

	static stringstream iss;
	iss.clear();
	iss.str(line);
	
	iss.ignore(256, '{');

	string label{};
	iss >> label;
	
	T search_val{};
	iss >> search_val;

	int size;
	iss >> size;

	iss.ignore(256, '{');

	vector<T> temp_vec;

	for (T temp; iss >> temp;)
		temp_vec.push_back(temp);

	if (iss.bad()) // 
		throw runtime_error("Error: istringstream is in bad state!");

	if (iss.eof()) { // Only if you modify the file while reading or something

		// Awful hack to allow strings to be read;
		if (typeid(search_val) == typeid(string)) {

			iss.clear();
			if (!temp_vec.empty()) {
				int size = temp_vec.size();
				iss << temp_vec.at(size - 1);
			}
		}
		else
			throw runtime_error("Error: istringstream did not expect eof.");
	}
	
	if (iss.fail())
		iss.clear();

	// Now ignore any whitespace before }
	iss.ignore(256, '}');
		
	static bool result;
	iss >> result;

	// Now assign:
	test.label = label;
	test.expected = search_val;
	test.result = result;
	test.seq = std::move(temp_vec);

	
	return is;
}

/**
 * Make a test for a specific Type T. This should be used when the type is
 * non-numerical and a random element cannot be created through random number
generators.
 *
 * @param os Reference to an ostream object
 * @param label Name of the test
 * @param expected Value that is to be searched in the list
 * @param length The size of the list
 * @param dictionary A vector that serves as the source for the list
 */
template<class T> void make_test(ostream &os, const string &label, T expected, int length, vector<T> dictionary) {
	os << "{ " << label << " " << expected << " ";

	vector<T> vec;
	vec.reserve(length);

	// Create a random collection from the dictionary:
	random_shuffle(dictionary.begin(), dictionary.end());
	int actual;
	int dict_length = dictionary.size();
	
	for (actual = 0; actual < length && actual < dict_length; actual++)
		vec.push_back(dictionary.at(actual));

	if (actual < length) {
		cerr << "Warning: Could not populate list with  " << length
			 << " item(s) (" << actual << " items populated instead)\n";
		
		vec.shrink_to_fit();
	}
	
	// Now populate the actual size:
	bool found = false;
	os << actual << " { ";
	for (const T& i : vec) {
		if (i == expected) found = true;
		os << i << " ";
	}

	os << "} " << found << " }";
}

template<class T> void make_test_batch(istream &input, ostream &output, int max_tests, vector<T> expected_list) {
	// Quick checks for input and output:

	if (!input || !output) {
		cerr << "Error: Could not open the following:\n";
		if (!input) cerr << "* Input File\n";
		if (!output) cerr << "* Output File\n";
		return;	   
	}
	
	if (max_tests < 0) {
		cerr << "Error: Max tests must be positive.\n";
		return;
	}
	
	if (max_tests > expected_list.size()) {
		cerr << "Error: Cannot make " << max_tests << " tests with "
			 << expected_list.size() << "expected values.\n";
		return;
	}

	// Use input to populate a dictionary:
	vector<T> dictionary;
	for (T temp; input >> temp;) {
		dictionary.push_back(temp);
	}
		
	// Now reset input
	input.clear();
	input.seekg(0);

	if (dictionary.empty()) {
		throw runtime_error("Error: Could not populate dictionary. Aborting.\n");	   							
	}

	// Create a distribution:
	std::uniform_int_distribution<size_t> dist {0, (dictionary.size() / 4)};
	std::mt19937 merse;
	
	// Now create as many tests as needed:
	for (int i = 0; i < max_tests; i++) {
		int size = dist(merse);
		make_test(output, "test-" + to_string(i), expected_list.at(i), size, dictionary);
		output << endl;
	}
	
}

void create_tests() {
	string filename = "../Dictionary_Lite.txt";
	ifstream dict {filename, ios_base::in};
	if (!dict) {
		cerr << "Error: Could not open \""<< filename << "\" !\n";
		exit(EXIT_FAILURE);
	}

	filename = "../Chapter26_02_String.txt";
	ofstream string_output {filename, ios_base::out};

	if (!string_output) {
		cerr << "Error: Could not open \""<< filename << "\" !\n";
		exit(EXIT_FAILURE);
	}


	filename = "../Chapter26_02_Double.txt";
	ofstream double_output {filename, ios_base::out};
	if (!double_output) {
		cerr << "Error: Could not open \""<< filename << "\" !\n";
		exit(EXIT_FAILURE);
	}

	// Make a batch of string tests
	cout << "Now making a batch of string tests...\n";
	vector<string> expected_strings = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog", "forever"};
	make_test_batch(dict, string_output, 10, expected_strings);


	// Now make a batch of float tests
	cout << "Now making a batch of float tests...\n";
	std::uniform_real_distribution<double> dist{0, 1000};
	std::mt19937 merse;
	vector<double> expected_doubles;

	for (int i = 0; i < 10; i++)
		expected_doubles.push_back(dist(merse));

	stringstream input_doubles;
	for (int i = 0; i < 100; i++)
		input_doubles << dist(merse) << " ";

	make_test_batch(input_doubles, double_output, 10, expected_doubles);

	cout << "Finished Creating Tests!" << endl;
}


template<class T> void print_sequence(vector<T> &vec) {
	cout << "{ ";
	for (const auto &i : vec)
		cout << i << " ";
	cout << "}\n";
}
void read_tests() {
	// Read String tests:
	string filename = "../Chapter26_02_String.txt";
	
	ifstream string_input {filename, ios_base::in};
	if (!string_input) {
		cerr << "Error: Could not open \""<< filename << "\" !\n";
		exit(EXIT_FAILURE);
	}

	filename = "../Chapter26_02_Double.txt";
	ifstream double_input {filename, ios_base::in};
	if (!double_input) {
		cerr << "Error: Could not open \""<< filename << "\" !\n";
		exit(EXIT_FAILURE);
	}

	// Now read string tests:
	for (Test<string> test; string_input >> test;) {
		if (test.label == "empty-string") {
			cout << "Skipping Empty String..\n";
			continue;
		}

		int result = simple_binary_search(test.seq, test.expected);
		if (result == -1)
			cout << "Could not find \"" << test.expected << "\" in ";
		else
			cout << "Found " << test.expected << " in ";

		print_sequence(test.seq);
	}


	// Now read double tests:
	for (Test<double> test; double_input >> test;) {
		if (test.label == "empty-string") {
			cout << "Skipping Empty String..\n";
			continue;
		}

		int result = simple_binary_search(test.seq, test.expected);
		if (result == -1)
			cout << "Could not find " << test.expected << " in ";
		else
			cout << "Found " << test.expected << " in ";

		print_sequence(test.seq);
	}
  
}

int main(void) {
	create_tests();
	cout << "Now testing tests...\n";
	read_tests();
}
