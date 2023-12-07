using System.Text.RegularExpressions;

public class Program {

    public const int part = 2;

    public enum HandType {
        HighCard = 1,
        OnePair = 2,
        TwoPairs = 3,
        ThreeOfAKind = 4,
        FullHouse = 5,
        FourOfAKind = 6,
        FiveOfAKind = 7,
    };

    public static HandType GetHandType(string card) {
        List<int> count;

        if (part == 2) {
            if (card == "*****")
                return HandType.FiveOfAKind;
            var jokersCount = card.Count(c => c == '*');
            count = card.Replace("*","").Distinct().ToDictionary(c => c, c => card.Count(c2 => c2 == c)).Values.OrderByDescending(v => v).ToList();
            count[0] += jokersCount;
        }
        else
            count = card.Distinct().ToDictionary(c => c, c => card.Count(c2 => c2 == c)).Values.OrderByDescending(v => v).ToList();

        return count[0] switch {
            5 => HandType.FiveOfAKind,
            4 => HandType.FourOfAKind,
            3 => count[1] == 2 ? HandType.FullHouse : HandType.ThreeOfAKind,
            2 => count[1] == 2 ? HandType.TwoPairs : HandType.OnePair,
            _ => HandType.HighCard
        };
    }

    public static void Main() {

        var entries = new List<(string card, long bid)>();

        var words = Regex.Split(File.ReadAllText("/Users/butjok/Aoc2023Day7/input"), @"\s+", RegexOptions.Singleline);
        for (var i = 0; i < words.Length; i += 2) {
            var card = new string(words[i].Select(c => c switch {
                'T' => 'a',
                'J' => part == 1 ? 'b' : '*',
                'Q' => 'c',
                'K' => 'd',
                'A' => 'e',
                _ => c
            }).ToArray());
            var bid = long.Parse(words[i + 1]);
            entries.Add((card, bid));
        }

        long rank = entries.Count;
        long result = 0;

        foreach (var entry in entries
                     .OrderByDescending(e => (int)GetHandType(e.card))
                     .ThenByDescending(e => e.card)) {
            Console.WriteLine($"{entry.card} {GetHandType(entry.card)}");
            result += rank * entry.bid;
            rank--;
        }

        Console.WriteLine(result);
    }
}