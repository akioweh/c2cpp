#include <numeric>
#include <ranges>
#include <string>
#include <vector>

using namespace std;


struct UF {
    static constexpr int offset = 'a';

    vector<int> parent;

    UF() : parent('z' - offset + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    char find(const char c) {
        auto x = c - offset;
        int pox;
        while ((pox = parent[x]) != x)
            tie(x, parent[x]) = {pox, parent[pox]};
        return static_cast<char>(x + offset);
    }

    void onion(const char c, const char d) {
        int x = find(c) - offset;
        int y = find(d) - offset;
        if (x == y)
            return;
        if (y < x)
            swap(x, y);
        parent[y] = x;
    }
};


class Solution {
public:
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        // ok we can do fancy ahh dsu thing but..
        // ok but why not

        UF ufo{};
        for (const auto [c, d] : views::zip(s1, s2))
            ufo.onion(c, d);

        for (auto &c : baseStr)
            c = ufo.find(c);

        return baseStr;
    }
};
