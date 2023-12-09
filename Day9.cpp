#include "Day.hpp"

std::vector<long long> Differentiate(const std::vector<long long>& values) {
	std::vector<long long> result;
	for (int i = 1; i < values.size(); i++)
		result.push_back(values[i] - values[i - 1]);
	return result;
}

void PrintSequence(const std::vector<long long>& sequence) {
	for (auto v : sequence)
		std::cout << v << " ";
	std::cout << '\n';
}

void PushFront(std::vector<long long>& sequence, long long value){
	sequence.insert(sequence.begin(), value);
}

template<>
long long Solve<9>(const std::string& input, Part part) {

	std::stringstream ss(input);
	std::string line;
	std::vector<std::vector<long long>> sequences;
	while (std::getline(ss, line)) {
		long long value;
		sequences.emplace_back();
		std::stringstream ss2(line);
		while (ss2 >> value)
			sequences.back().push_back(value);
	}

	long long result = 0;

	for (auto sequence : sequences) {

		std::vector<std::vector<long long>> values{sequence};
		while (sequence.size() > 1 && !std::all_of(sequence.begin(), sequence.end(), [](long long v) { return v == 0; })) {
			sequence = Differentiate(sequence);
			values.push_back(sequence);
		}

		if (part == Part::One) {
			values.back().push_back(0);
			for (auto i = static_cast<int>(values.size()) - 2; i >= 0; i--)
				values[i].push_back(values[i].back() + values[i + 1].back());
			result += values[0].back();
		}
		else {
			PushFront(values.back(), 0);
			for (auto i = static_cast<int>(values.size()) - 2; i >= 0; i--)
				PushFront(values[i], values[i].front() - values[i + 1].front());
			result += values[0].front();
		}

		for (auto& v : values)
			PrintSequence(v);
		std::cout << "\n";
	}

	return result;
}

template<>
std::string GetExampleInput<9, 1>() {
	return "0 3 6 9 12 15\n"
		   "1 3 6 10 15 21\n"
		   "10 13 16 21 30 45";
}