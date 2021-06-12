/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/12/2021 at 02:00 PM
 * 
 * Chapter26_Drill.h
 * 
 * -----------------------------------------------------------------------------
 */

#pragma once
#ifndef CHAPTER26_DRILL_H
#define CHAPTER26_DRILL_H

#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <sstream>


struct Test {
	std::string label{};
	int val{};
	std::vector<int> seq;
	bool result{};
};


// Function Declarations
std::istream& operator>>(std::istream &is, Test &t);

#endif
