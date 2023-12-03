#include "Day.hpp"
#include <sstream>

const int r = 0, g = 1, b = 2;

std::vector<std::array<int, 3>> ReadGame(const std::string& line, int& gameNumber) {

	static std::unordered_map<char, int> colorMap{{'r', r},
												  {'g', g},
												  {'b', b}};

	std::string token;
	int number;
	std::vector<std::array<int, 3>> cubeSets{{0, 0, 0}};

	std::stringstream ss(line);
	ss >> token >> gameNumber >> token;
	while (ss >> number && ss >> token) {
		cubeSets.back()[colorMap[token[0]]] = number;
		if (token.back() == ';')
			cubeSets.emplace_back();
	}
	return cubeSets;
}

bool IsValidCubeSet(const std::array<int, 3>& cubeSet) {
	return cubeSet[0] <= 12 && cubeSet[1] <= 13 && cubeSet[2] <= 14;
}

template<>
long long Solve<2>(const std::string& input, Part part) {

	std::stringstream ss(input);
	std::string line, token;

	long long result = 0;
	while (std::getline(ss, line)) {

		int gameNumber;
		auto cubeSets = ReadGame(line, gameNumber);

		if (part == Part::One && std::all_of(cubeSets.cbegin(), cubeSets.cend(), IsValidCubeSet))
			result += gameNumber;

		if (part == Part::Two) {
			std::array<int, 3> cubesRequired{0, 0, 0};
			for (const auto& cubeSet : cubeSets)
				for (int color = r; color <= b; color++)
					cubesRequired[color] = std::max(cubesRequired[color], cubeSet[color]);
			result += cubesRequired[r] * cubesRequired[g] * cubesRequired[b];
		}
	}
	return result;
}

template<>
std::string GetExampleInput<2, 1>() {
	return "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n"
		   "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n"
		   "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\n"
		   "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\n"
		   "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
}