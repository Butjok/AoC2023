#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <iostream>

#include "FileSystem.hpp"

enum class Part {
	One, Two
};

template<int dayNumber>
long long Solve(const std::string& input, Part part) {
	std::cerr << "Day " << dayNumber << " is not implemented.\n";
	abort();
}

template<int dayNumber>
std::string GetInput() {
	return FileSystem::ReadAsString("Input.txt", dayNumber);
}

template<int dayNumber, int exampleNumber>
std::string GetExampleInput() {
	return FileSystem::ReadAsString("Example" + std::to_string(exampleNumber) + ".txt", dayNumber);
}

template<int dayNumber>
void Run() {
	std::cout << "Part 1: " << Solve<dayNumber>(GetInput<dayNumber>(), Part::One) << "\n";
	std::cout << "Part 2: " << Solve<dayNumber>(GetInput<dayNumber>(), Part::Two) << "\n";
}