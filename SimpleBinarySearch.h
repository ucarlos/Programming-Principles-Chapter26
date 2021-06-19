/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/13/2021 at 01:11 AM
 * 
 * SimpleBinarySearch.hpp
 * 
 * -----------------------------------------------------------------------------
 */

#pragma once
#ifndef SIMPLE_BINARY_SEARCH_H
#define SIMPLE_BINARY_SEARCH_H
#include <iostream>
#include <vector>
#include <cstdint>

template<class T> std::int64_t simple_binary_search(std::vector<T> vec, T item);

template<class T> std::int64_t simple_binary_search(std::vector<T> vec, T item) {
	std::int64_t begin = 0;
	std::int64_t end = vec.size() - 1;

	while (begin <= end) {
		std::int64_t mid = (begin + end) / 2;
		T result = vec.at(mid);
		if (result == item)
			return mid;
		else if (result < item)
			begin = mid + 1;
		else
			end = mid - 1;
	}

	return -1; 	// Otherwise, return -1 if not found:

}


//------------------------------------------------------------------------------
// Added for Chapter26_03
//------------------------------------------------------------------------------
template<class T, class Comp>
std::int64_t simple_binary_search(std::vector<T> vec, T item, Comp compare);



/**
 * Search a vector for a given item, using a 3 way compare function.
 * This compare function should return a value equal, less than
 * or greater than zero.
 * @param vec 
 * @param item 
 * @param compare
 */
template<class T, class Comp>
std::int64_t simple_binary_search(std::vector<T> vec, T item, Comp compare) {
	std::int64_t begin = 0;
	std::int64_t end = vec.size() - 1;

	while (begin <= end) {
		std::int64_t mid = (begin + end) / 2;
		T value = vec.at(mid);

		auto result = compare(value, item);
		if (result == 0) return mid;
		else if (result < 0)
			begin = mid + 1;
		else
			end = mid - 1;
				
	}

	return -1; // Not found
}

#endif
