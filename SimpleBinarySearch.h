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

template<class T> std::size_t simple_binary_search(std::vector<T> vec, T item);

template<class T> std::size_t simple_binary_search(std::vector<T> vec, T item) {
	int begin = 0;
	int end = vec.size() - 1;

	while (begin <= end) {
		int mid = (begin + end) / 2;
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

#endif
