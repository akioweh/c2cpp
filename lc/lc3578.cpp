#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;

class Solution {
public:
    int countPartitions(const vector<int> &nums, const int k) {
        const auto n = static_cast<int>(nums.size());
        auto min_q = deque<pair<int, int>>();
        auto max_q = deque<pair<int, int>>();
        auto dp = vector<int>(n, 0);
        auto dp_pfs = vector<int>(n + 1, 0);
        auto l = 0;
        min_q.emplace_back(nums.front(), 0);
        max_q.emplace_back(nums.front(), 0);
        dp[0] = 1;
        dp_pfs[1] = 1;
        for (auto i = 1; i < n; ++i) {
            const auto v = nums[i];
            // push queues
            while (!max_q.empty() && max_q.back().first <= v)
                max_q.pop_back();
            max_q.emplace_back(v, i);
            while (!min_q.empty() && min_q.back().first >= v)
                min_q.pop_back();
            min_q.emplace_back(v, i);
            // pop until k is satisfied
            while (max(max_q.front().first, v) - min(min_q.front().first, v) > k) {
                if (max_q.front().second < min_q.front().second) {
                    l = max_q.front().second + 1;
                    max_q.pop_front();
                } else {
                    l = min_q.front().second + 1;
                    min_q.pop_front();
                }
            }
            dp[i] += ((dp_pfs[i] - dp_pfs[max(l - 1, 0)] + (l == 0)) % MOD + MOD) % MOD;
            dp_pfs[i + 1] = (dp_pfs[i] + dp[i]) % MOD;
        }

        return dp.back();
    }
};
