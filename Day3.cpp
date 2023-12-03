#include "Day.hpp"

template<>
long long Solve<3>(const std::string& input, Part part) {

	std::vector<std::string> map, originalMap;
	std::stringstream ss(input);
	std::string line;
	while (std::getline(ss, line))
		map.push_back(line);
	originalMap = map;

	auto height = map.size();
	auto width = map[0].size();

	long long result = 0;
	for (auto y = 0; y < height; y++)
		for (auto x = 0; x < width; x++) {

			// found symbol
			if (map[y][x] != '.' && !std::isdigit(map[y][x])) {

				// need to reset the map to the initial state for part 2
				if (part == Part::Two)
					map = originalMap;

				auto symbol = map[y][x];
				std::vector<int> numbers;

				for (auto ny = y - 1; ny <= y + 1; ny++)
					for (auto nx = x - 1; nx <= x + 1; nx++) {
						if (nx < 0 || nx >= width || ny < 0 || ny >= height)
							continue;

						// found number
						if (std::isdigit(map[ny][nx])) {

							// need to find number's left and right bounds
							auto start = nx, end = nx;
							while (start - 1 >= 0 && std::isdigit(map[ny][start - 1])) start--;
							while (end + 1 < width && std::isdigit(map[ny][end + 1])) end++;

							int number = 0;
							for (auto i = start; i <= end; i++) {
								number = number * 10 + map[ny][i] - '0';
								// erase so we don't encounter it multiple times for this symbol
								map[ny][i] = '.';
							}

							if (part == Part::One)
								result += number;

							if (part == Part::Two && symbol == '*')
								numbers.push_back(number);
						}
					}

				if (part == Part::Two && symbol == '*' && numbers.size() == 2)
					result += numbers[0] * numbers[1];
			}
		}
	return result;
}

template<>
std::string GetExampleInput<3, 1>() {
	return "467..114..\n"
		   "...*......\n"
		   "..35..633.\n"
		   "......#...\n"
		   "617*......\n"
		   ".....+.58.\n"
		   "..592.....\n"
		   "......755.\n"
		   "...$.*....\n"
		   ".664.598..";
}