#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int countPartitions(vector<int> &nums) {
        const auto tot = accumulate(nums.begin(), nums.end(), 0);
        auto res = 0;
        auto acc = 0;
        nums.pop_back();
        for (const auto v : nums) {
            acc += v;
            if ((tot - 2 * acc) % 2 == 0)
                ++res;
        }
        return res;
    }
};
