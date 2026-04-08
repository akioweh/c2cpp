#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;


class Solution {
public:
    int xorAfterQueries(vector<int> &nums, vector<vector<int>> &queries) {
        for (const auto &vec : queries) {
            const auto l = vec[0];
            const auto r = vec[1];
            const auto k = vec[2];
            const auto v = vec[3];
            auto idx = l;
            while (idx <= r) {
                nums[idx] = (static_cast<long long>(nums[idx]) * v) % MOD;
                idx += k;
            }
        }

        return reduce(nums.begin(), nums.end(), 0, bit_xor{});
    }
};
