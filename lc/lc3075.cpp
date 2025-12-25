#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    long long maximumHappinessSum(vector<int> &happiness, int k) {
        ranges::partial_sort(happiness, happiness.begin() + k, greater{});
        auto res = accumulate(happiness.begin(), happiness.begin() + k, 0LL);
        for (const auto &[i, h] : happiness | views::enumerate | views::take(k))
            res -= min(h, static_cast<int>(i));
        return res;
    }
};
