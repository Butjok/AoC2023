#pragma once

#include <string>
#include <fstream>

namespace FileSystem {
	std::ifstream OpenFile(const std::string& filename, int dayNumber);
	std::string ReadAsString(std::ifstream& input);
	std::string ReadAsString(const std::string& filename, int dayNumber);
}