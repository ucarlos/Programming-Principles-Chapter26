/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 05/31/2021 at 06:21 PM
 *
 * Chapter26_12.cc
 * Write a program that generates random floating-point numbers and sort
 * them using std::sort(). Measure the time used to sort 500,000 double s
 * and 5,000,000 double s.
 *
 * On my desktop computer, it takes 1 second to sort 500,000 values, while
 * sorting 5 million values takes 4 seconds.
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

const int SIZE1 = 500000;
const int SIZE2 = 5000000;

using distribution = std::uniform_real_distribution<double>;


void sort_500k(vector<double> &vec, distribution &dist, std::mt19937 &merse) {
	for (int i = 0; i < SIZE1; i++)
		vec.push_back(dist(merse));

	time_t start = time(nullptr);
	sort(vec.begin(), vec.end());
	time_t end = time(nullptr);

	cout << "Sorting " << SIZE1 << " values took " << (end - start) << " seconds.\n";
}

void sort_5M(vector<double> &vec, distribution &dist, std::mt19937 &merse) {
	for (int i = 0; i < SIZE2; i++)
		vec.push_back(dist(merse));

	time_t start = time(nullptr);
	sort(vec.begin(), vec.end());
	time_t end = time(nullptr);

	
	cout << "Sorting " << SIZE2 << " values took " << (end - start) << " seconds.\n";

}


int main(void) {
	vector<double> vec{SIZE1};

	std::random_device rand;
	std::mt19937 merse;
	distribution dist{0, 5000000};

	sort_500k(vec, dist, merse);
	
	vec.clear();
	vec.resize(SIZE2);
	
	sort_5M(vec, dist, merse);
	

}

