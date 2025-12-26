#include <bits/stdc++.h>
#include <limits>

using namespace std;


class Solution {
public:
    int maxProfit(const int n, const vector<int> &present, const vector<int> &future,
                  const vector<vector<int>> &hierarchy, const int budget) {
        auto children = vector(n, vector<int>());
        for (const auto &e : hierarchy)
            children[e.front() - 1].push_back(e.back() - 1);

        auto dp_t = vector(n, pair{vector<int>(), vector<int>()}); // {normal, discount}

        const auto mckp = [](const auto &buckets, const int cap) {
            auto _dp = vector(cap + 1, numeric_limits<int>::min() / 2);
            _dp[0] = 0;
            for (const auto items : buckets) {
                auto _new_dp = _dp;
                for (const auto [_w, _v] : views::enumerate(items)) {
                    for (auto w = cap; w >= _w; --w)
                        _new_dp[w] = max(_new_dp[w], _dp[w - _w] + _v);
                }
                _dp = _new_dp;
            }
            return _dp;
        };

        const function<void(int)> calc = [&future, &present, &children, &dp_t, budget, &mckp, &calc](const auto u) {
            for (const auto v : children[u])
                calc(v);
            // now we do multiple-chocie (bucket) knapsack
            auto &dih = dp_t[u].first;
            auto &dct = dp_t[u].second;
            const auto child_dps = children[u] | views::transform([&](const int v) -> auto & { return dp_t[v]; });
            // no buy this
            dih = dct = mckp(child_dps | views::keys, budget);
            // buy this
            if (budget >= present[u]) {
                const auto tmp1 = mckp(child_dps | views::values, budget - present[u]);
                for (auto c = present[u]; c <= budget; ++c)
                    dih[c] = max(dih[c], tmp1[c - present[u]] + future[u] - present[u]);
            }
            if (budget >= present[u] / 2) {
                const auto tmp2 = mckp(child_dps | views::values, budget - (present[u] / 2));
                for (auto c = present[u] / 2; c <= budget; ++c)
                    dct[c] = max(dct[c], tmp2[c - present[u] / 2] + future[u] - present[u] / 2);
            }
        };

        calc(0);
        return *ranges::max_element(dp_t[0].first);
    }
};
