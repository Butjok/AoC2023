#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

struct Range { long long start, end; };
struct Mapping { Range from, to; };

bool TryIntersect(const Range& a, const Range& b, Range& intersection) {
	auto lesser = a, greater = b;
	if (lesser.start > greater.start)
		std::swap(lesser, greater);
	if (lesser.end >= greater.start) {
		intersection.start = greater.start;
		intersection.end = std::min(lesser.end, greater.end);
		return true;
	}
	else
		return false;
}

std::vector<Mapping> SubdivideMapping(const Mapping& inputMapping, const std::vector<Mapping>& mappings) {
	std::vector<Mapping> result;
	for (const auto& mapping : mappings) {
		Range intersection;
		if (TryIntersect(inputMapping.to, mapping.from, intersection)) {
			auto offset = mapping.to.start - mapping.from.start;
			result.push_back(Mapping{ { intersection.start, intersection.end }, { intersection.start + offset, intersection.end + offset } });
		}
	}
	return result;
}

bool TryAddIndentityMapping(const Range& range, std::vector<Mapping>& mappings) {
	if (range.end < range.start) return false;
	mappings.push_back(Mapping{ range, range });
	return true;
}
void FillGaps(std::vector<Mapping>& mappings) {
	std::vector<Mapping> result;
	std::sort(mappings.begin(), mappings.end(), [](const Mapping& a, const Mapping& b) { return a.from.start < b.from.start; });
	for (auto i = 0; i < mappings.size(); i++) {
		const auto& current = mappings[i];
		if (i == 0)
			TryAddIndentityMapping({ 0, current.from.start - 1 }, result);
		else {
			const auto& previous = mappings[i - 1];
			TryAddIndentityMapping({ previous.from.end + 1, current.from.start - 1 }, result);
		}
		result.push_back(current);
	}
	if (mappings.size() > 0) {
		const auto& last = mappings[mappings.size() - 1];
		TryAddIndentityMapping({ last.from.end + 1, 9223372036854775000ll }, result);
	}
	mappings = std::move(result);
}

enum class Part { One, Two };

struct Input {
	std::vector<Mapping> seeds, seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation;
};
Input ReadInput(std::istream& input, Part part) {

	std::string token;
	Input result;
	std::vector<Mapping>* targetMappingList = nullptr;

	while (input >> token) {

		auto oldTargetMappingList = targetMappingList;
		if (token == "map:" || token == "seeds:")    continue;
		else if (token == "seed-to-soil")            targetMappingList = &result.seedToSoil;
		else if (token == "soil-to-fertilizer")      targetMappingList = &result.soilToFertilizer;
		else if (token == "fertilizer-to-water")     targetMappingList = &result.fertilizerToWater;
		else if (token == "water-to-light")          targetMappingList = &result.waterToLight;
		else if (token == "light-to-temperature")    targetMappingList = &result.lightToTemperature;
		else if (token == "temperature-to-humidity") targetMappingList = &result.temperatureToHumidity;
		else if (token == "humidity-to-location")    targetMappingList = &result.humidityToLocation;
		if (targetMappingList != oldTargetMappingList) continue;

		if (targetMappingList == nullptr) {
			if (part == Part::One) {
				auto seed = std::stoll(token);
				result.seeds.emplace_back(Mapping{ {seed,seed}, {seed,seed} });
			}
			else {
				long long start, length;
				start = std::stoll(token);
				input >> length;
				result.seeds.emplace_back(Mapping{ {start,start+length-1},{start,start + length - 1} });
			}
		}
		else {
			long long destinationRangeStart, sourceRangeStart, length;
			input >> sourceRangeStart >> length;
			destinationRangeStart = std::stoll(token);
			targetMappingList->push_back({ { sourceRangeStart, sourceRangeStart + length - 1 }, { destinationRangeStart, destinationRangeStart + length - 1 } });
		}
	}

	FillGaps(result.seedToSoil);
	FillGaps(result.soilToFertilizer);
	FillGaps(result.fertilizerToWater);
	FillGaps(result.waterToLight);
	FillGaps(result.lightToTemperature);
	FillGaps(result.temperatureToHumidity);
	FillGaps(result.humidityToLocation);

	return result;
}

int main() {

	std::ifstream file("C:\\Users\\v.fedotov\\source\\repos\\Aoc2023Day5\\Input.txt");
	assert(file);

	auto input = ReadInput(file, Part::Two);
	long long result = std::numeric_limits<long long>::max();
	for (const auto& seed : input.seeds) {
		std::vector<Mapping> s = SubdivideMapping(seed, input.seedToSoil);
		for (const auto& it : s) {
			std::vector<Mapping> s2 = SubdivideMapping(it, input.soilToFertilizer);
			for (const auto& it2 : s2) {
				std::vector<Mapping> s3 = SubdivideMapping(it2, input.fertilizerToWater);
				for (const auto& it3 : s3) {
					std::vector<Mapping> s4 = SubdivideMapping(it3, input.waterToLight);
					for (const auto& it4 : s4) {
						std::vector<Mapping> s5 = SubdivideMapping(it4, input.lightToTemperature);
						for (const auto& it5 : s5) {
							std::vector<Mapping> s6 = SubdivideMapping(it5, input.temperatureToHumidity);
							for (const auto& it6 : s6) {
								std::vector<Mapping> s7 = SubdivideMapping(it6, input.humidityToLocation);
								for (const auto& it7 : s7)
									result = std::min(result, it7.to.start);
							}
						}
					}
				}
			}
		}
	}
	std::cout << result << '\n';

	return 0;
}
