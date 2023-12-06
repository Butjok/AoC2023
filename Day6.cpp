#include "Day.hpp"

template<>
long long Solve<6>(const std::string& input, Part part)
{
	std::stringstream ss(input);
	std::vector<long long> timeLimits, records;
	std::string token;
	std::vector<long long> *target = nullptr;
	while (ss >> token) {
		if (token == "Time:") target = &timeLimits;
		else if (token == "Distance:") target = &records;
		else target->push_back(std::stoll(token));
	}

	if (part == Part::Two){
		std::string actualTimeLimit;
		std::string actualRecord;
		for (auto i =0 ;i < timeLimits.size();i++){
			actualRecord += std::to_string(records[i]);
			actualTimeLimit += std::to_string(timeLimits[i]);
		}
		records.clear();
		timeLimits.clear();
		records.push_back(std::stoll(actualRecord));
		timeLimits.push_back(std::stoll(actualTimeLimit));
	}

	long long result = 1;
	for (auto i = 0;i < timeLimits.size();i++) {
		auto T = timeLimits[i];
		auto R = records[i];
		// distance: D(t) = tT - t^2
		// need solve equation: D(t) - (R+1) = 0 <=> -t^2 + tT - R-1 = 0
		auto a = -1ll, b = T, c = -R-1;
		auto d = b * b - 4 * a * c;
		if (d < 0)
			result *= 0;
		auto tLow = static_cast<long long>(std::ceil((-b + std::sqrt(d)) / (2 * a)));
		auto tHigh = static_cast<long long>(std::floor((-b - std::sqrt(d)) / (2 * a)));
		std::cout << T << ' ' << R << ": " << tLow << ' ' << tHigh << '\n';
		result *= tHigh - tLow + 1;
	}
	std::cout << result << '\n';

	return 0;
}

template<>
std::string GetExampleInput<6,1>(){
	return "Time:      7  15   30\n"
		   "Distance:  9  40  200";
}

template<>
std::string GetInput<6>() {
	return "Time:        59     68     82     74\n"
		   "Distance:   543   1020   1664   1022";
}