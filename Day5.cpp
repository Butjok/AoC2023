#include "Day.hpp"
#include <numeric>

struct MapEntry {
	long long destinationRangeStart, sourceRangeStart, length;
	bool InRange(long long inputValue) const {
		return inputValue >= sourceRangeStart && inputValue <= sourceRangeStart + length;
	}
	long Convert(long long inputValue) const {
		return destinationRangeStart + (inputValue - sourceRangeStart);
	}
};
long long Convert(const std::vector<MapEntry>& entries, long long inputValue) {
	for (auto& entry : entries)
		if (entry.InRange(inputValue))
			return entry.Convert(inputValue);
	return inputValue;
}

template<>
long long Solve<5>(const std::string& input, Part part) {

	std::stringstream ss(input);
	std::string token;
	std::vector<long long> seeds;
	std::vector<std::pair<long long, long long>> seedRanges;
	std::vector<MapEntry> seedToSoilMap, soilToFertilizerMap, fertilizerToWaterMap, waterToLightMap, lightToTemperatureMap, temperatureToHumidityMap, humidityToLocationMap;
	std::vector<MapEntry>* targetMap = nullptr;

	while (ss >> token) {

		auto oldTargetMap = targetMap;
		if (token == "map:" || token == "seeds:") continue;
		else if (token == "seed-to-soil") targetMap = &seedToSoilMap;
		else if (token == "soil-to-fertilizer") targetMap = &soilToFertilizerMap;
		else if (token == "fertilizer-to-water") targetMap = &fertilizerToWaterMap;
		else if (token == "water-to-light") targetMap = &waterToLightMap;
		else if (token == "light-to-temperature") targetMap = &lightToTemperatureMap;
		else if (token == "temperature-to-humidity") targetMap = &temperatureToHumidityMap;
		else if (token == "humidity-to-location") targetMap = &humidityToLocationMap;
		if (targetMap != oldTargetMap) continue;

		if (targetMap == nullptr) {
			if (part == Part::One)
				seeds.push_back(std::stoll(token));
			else {
				long long start, length;
				ss >> length;
				start = std::stoll(token);
				seedRanges.emplace_back(start, length);
			}
		}
		else {
			long long destinationRangeStart, sourceRangeStart, length;
			ss >> sourceRangeStart >> length;
			destinationRangeStart = std::stoll(token);
			targetMap->push_back({destinationRangeStart, sourceRangeStart, length});
		}
	}

	std::vector<long long> allSeeds;
	if (part == Part::One)
		allSeeds = seeds;
	else {
		for (const auto& range : seedRanges)
			for (auto i = range.first; i < range.first + range.second; i++)
				allSeeds.push_back(i);
	}

	long long result = std::numeric_limits<long long>::max();
	for (auto seed: allSeeds) {
		auto soil = Convert(seedToSoilMap, seed);
		auto fertilizer = Convert(soilToFertilizerMap, soil);
		auto water = Convert(fertilizerToWaterMap, fertilizer);
		auto light = Convert(waterToLightMap, water);
		auto temperature = Convert(lightToTemperatureMap, light);
		auto humidity = Convert(temperatureToHumidityMap, temperature);
		auto location = Convert(humidityToLocationMap, humidity);
		result = std::min(result, static_cast<long long>(location));
	}
	return result;
}

template<>
std::string GetExampleInput<5, 1>() {
	return "seeds: 79 14 55 13\n"
		   "\n"
		   "seed-to-soil map:\n"
		   "50 98 2\n"
		   "52 50 48\n"
		   "\n"
		   "soil-to-fertilizer map:\n"
		   "0 15 37\n"
		   "37 52 2\n"
		   "39 0 15\n"
		   "\n"
		   "fertilizer-to-water map:\n"
		   "49 53 8\n"
		   "0 11 42\n"
		   "42 0 7\n"
		   "57 7 4\n"
		   "\n"
		   "water-to-light map:\n"
		   "88 18 7\n"
		   "18 25 70\n"
		   "\n"
		   "light-to-temperature map:\n"
		   "45 77 23\n"
		   "81 45 19\n"
		   "68 64 13\n"
		   "\n"
		   "temperature-to-humidity map:\n"
		   "0 69 1\n"
		   "1 0 69\n"
		   "\n"
		   "humidity-to-location map:\n"
		   "60 56 37\n"
		   "56 93 4";
}

template<>
void Run<5>() {
	std::cout << Solve<5>(GetExampleInput<5,1>(), Part::One) << '\n';
	std::cout << Solve<5>(GetExampleInput<5,1>(), Part::Two) << '\n';
}