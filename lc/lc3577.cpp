#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;


int fact(int x) {
    auto res = 1;
    while (x)
        res = (1ll * res * x--) % MOD;
    return res;
}


class Solution {
public:
    int countPermutations(const vector<int> &complexity) {
        const auto n = static_cast<int>(complexity.size());
        const auto l = *ranges::min_element(complexity);
        if (ranges::count(complexity, l) > 1)
            return 0;
        if (complexity.front() != l)
            return 0;
        return fact(n - 1);
    }
};
