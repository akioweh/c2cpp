#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minimumDistance(vector<int> &nums) {
        auto idxs = map<int, vector<int>>();
        for (const auto [i, v] : views::enumerate(nums))
            idxs[v].push_back(i);

        auto res = numeric_limits<int>::max();
        for (auto [v, vec] : idxs) {
            if (vec.size() < 3)
                continue;
            ranges::sort(vec);
            for (const auto i : views::iota(0uz, vec.size() - 2))
                res = min(res, 2 * (vec[i + 2] - vec[i]));
        }
        return res == numeric_limits<int>::max() ? -1 : res;
    }
};
