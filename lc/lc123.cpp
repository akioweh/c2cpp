#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int maxProfit(vector<int> &prices) {
        const auto n = static_cast<int>(prices.size());
        auto pre_profit = vector<int>(n + 1);
        auto suf_profit = vector<int>(n + 1);
        pre_profit[0] = numeric_limits<int>::min();
        auto cur_min = numeric_limits<int>::max() / 2;
        for (const auto i : views::iota(0, n)) {
            pre_profit[i + 1] = max(pre_profit[i], prices[i] - cur_min);
            cur_min = min(cur_min, prices[i]);
        }
        auto cur_max = numeric_limits<int>::min() / 2;
        for (auto i = n; i--;) {
            suf_profit[i] = max(suf_profit[i + 1], cur_max - prices[i]);
            cur_max = max(cur_max, prices[i]);
        }

        auto res = 0;
        for (const auto i : views::iota(0, n + 1))
            res = max(res, pre_profit[i] + suf_profit[i]);
        return res;
    }
};
