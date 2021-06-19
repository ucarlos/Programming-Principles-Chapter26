/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/19/2021 at 02:44 PM
 *
 * Chapter26_03.cc
 * Repeat exercise 1 with the version of binary_search that takes a
 * comparison criterion.
 * -----------------------------------------------------------------------------
 */

#include "Chapter26_Drill.h"
#include "SimpleBinarySearch.h"
#include <random>
using namespace std;


class Compare {
public:
	Compare() =default;
	Compare(int64_t v) : val{v} { }

	bool operator()(int64_t val1, int64_t val2) {
		if (val1 == val2) return 0;
		else
			return (val1 < val2)? -1 : 1;
	}
private:	
	int64_t val;
};


int main(void) {
	
	uniform_int_distribution<int64_t> distribution{0, 100000};
	std::mt19937 merse{};

	vector<int64_t> vec;
	for (int i = 0; i < 100; i++)
		vec.push_back(distribution(merse));

	// Now sort the sequence:
	sort(vec.begin(), vec.end());

	int64_t value = 10;
	Compare compare{};
	
	auto result = simple_binary_search(vec, value, compare);

	cout << "Is " << value << " located in the sequence? ";
	cout << ((result != -1) ? "Yes\n" : "No\n");
}
