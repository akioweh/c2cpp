#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        const auto n = static_cast<int>(encodedText.size());
        const auto cols = n / rows;
        auto res = ""s;
        for (const auto i : views::iota(0, cols)) {
            for (const auto o : views::iota(0, rows)) {
                const auto idx = o * cols + i + o;
                if (idx >= n)
                    continue;
                res += encodedText[idx];
            }
        }
        while (!res.empty() && res.back() == ' ')
            res.pop_back();
        return res;
    }
};
