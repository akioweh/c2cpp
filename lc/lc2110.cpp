#include <bits/stdc++.h>;

using namespace std;


class Solution {
public:
    long long getDescentPeriods(vector<int> &prices) {
        for (auto [i, v] : views::enumerate(prices))
            v += i;
        long long res = 0;
        for (const auto &chunk : prices | views::chunk_by(equal_to{})) {
            const auto n = ranges::distance(chunk);
            res += static_cast<long long>(n) * (n + 1) / 2;
        }
        return res;
    }
};
