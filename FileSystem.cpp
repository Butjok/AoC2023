#include <cassert>
#include <sstream>

#include "FileSystem.hpp"

namespace FileSystem {

	static const char* inputDirectory = "/Users/butjok/CLionProjects/AoC2023/Inputs/";

	std::ifstream OpenFile(const std::string& filename, int dayNumber) {
		std::ifstream input(FileSystem::inputDirectory + std::to_string(dayNumber) + "/" + filename);
		assert(input.is_open());
		return input;
	}
	std::string ReadAsString(std::ifstream& input) {
		std::stringstream buffer;
		buffer << input.rdbuf();
		return buffer.str();
	}
	std::string ReadAsString(const std::string& filename, int dayNumber) {
		auto input = OpenFile(filename, dayNumber);
		return ReadAsString(input);
	}
}