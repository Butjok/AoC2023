#include "Day.hpp"
#include <optional>
#include <algorithm>
#include <numeric>
#include <map>

struct Card {
	int number = 0;
	size_t matchesCount = 0;

	Card() = default;
	Card(int number, const std::vector<int>& winningNumbers, const std::vector<int>& myNumbers)
			: number(number) {
		matchesCount = std::count_if(myNumbers.begin(), myNumbers.end(), [&](int n) {
			return std::find(winningNumbers.begin(), winningNumbers.end(), n) != winningNumbers.end();
		});
	}
};

template<>
long long Solve<4>(const std::string& input, Part part) {

	std::stringstream ss(input);
	std::string line;
	std::map<int, Card> cards;
		std::unordered_map<int, int> cardsCount;

	while (std::getline(ss, line)) {

		std::stringstream ss2(line);
		std::string token;
		int cardNumber;
		std::vector<int> winningNumbers, myNumbers;

		ss2 >> token >> cardNumber >> token;
		while (ss2 >> token && token != "|")
			winningNumbers.push_back(std::stoi(token));
		while (ss2 >> token)
			myNumbers.push_back(std::stoi(token));

		cards[cardNumber] = Card(cardNumber, winningNumbers, myNumbers);
		cardsCount[cardNumber] = 1;
	}

	if (part == Part::One) {
		std::vector<int> points;
		std::transform(cards.begin(), cards.end(), std::back_inserter(points), [](const std::pair<int, Card>& card) {
			return card.second.matchesCount == 0 ? 0 : 1 << (card.second.matchesCount - 1);
		});
		return std::reduce(points.begin(), points.end());
	}
	else {
		for (auto& [_,card] : cards)
			for (auto i = card.number + 1; i <= card.number + card.matchesCount && i <= cards.size(); i++)
				cardsCount[i] += cardsCount[card.number];
		return std::reduce(cardsCount.begin(), cardsCount.end(), 0, [](int a, const std::pair<int, int>& b) {
			return a + b.second;
		});
	}
}

template<>
std::string GetExampleInput<4, 1>() {
	return "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n"
		   "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n"
		   "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1\n"
		   "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n"
		   "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n"
		   "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11";
}
