#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int minimumIncrements(vector<int> &nums, vector<int> &target) {
        const auto n = static_cast<int>(nums.size());
        ranges::sort(target);
        const auto it = ranges::unique(target);
        target.erase(it.begin(), it.end());
        const auto m = static_cast<int>(target.size());
        auto resi = vector(m, vector<int>(n));
        for (const auto [m, t] : views::enumerate(target)) {
            for (const auto [i, v] : views::enumerate(nums))
                resi[m][i] = (t - (v % t)) % t;
        }
    }
};
