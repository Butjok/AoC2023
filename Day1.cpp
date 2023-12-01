#include "Day.hpp"
#include <string_view>

template<>
long long Solve<1>(const std::string& input, Part part) {

	static std::vector<std::string> words{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

	std::stringstream ss(input);
	std::string line;
	std::vector<int> digits;

	long long result = 0;
	while (std::getline(ss, line)) {

		for (auto i = line.cbegin(); i != line.cend(); i++) {
			if (std::isdigit(*i))
				digits.push_back(*i - '0');
			else if (part == Part::Two) {
				auto word = std::find_if(words.cbegin(), words.cend(), [&](const std::string& word) {
					return std::string_view(i, i + word.size()) == word;
				});
				if (word != words.cend())
					digits.push_back(word - words.cbegin() + 1);
			}
		}

		result += digits[0] * 10 + *digits.crbegin();
		digits.clear();
	}
	return result;
}

template<>
std::string GetExampleInput<1, 1>() {
	return "1abc2\n"
		   "pqr3stu8vwx\n"
		   "a1b2c3d4e5f\n"
		   "treb7uchet";
}

template<>
std::string GetExampleInput<1, 2>() {
	return "two1nine\n"
		   "eightwothree\n"
		   "abcone2threexyz\n"
		   "xtwone3four\n"
		   "4nineeightseven2\n"
		   "zoneight234\n"
		   "7pqrstsixteen";
}
