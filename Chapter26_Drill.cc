/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/12/2021 at 02:02 PM
 * 
 * Chapter26_Drill.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include "Chapter26_Drill.h"
using namespace std;
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
