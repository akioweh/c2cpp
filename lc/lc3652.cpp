#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    long long maxProfit(const vector<int> &prices, const vector<int> &strategy, const int k) {
        const auto n = static_cast<int>(prices.size());
        const auto base = views::zip(prices, strategy) |
                views::transform([](const auto &tup) { return get<0>(tup) * get<1>(tup); });
        auto pfs_base = vector{0ll};
        pfs_base.reserve(n + 1);
        inclusive_scan(base.begin(), base.end(), back_inserter(pfs_base), plus{}, 0ll);
        auto pfs_price = vector{0ll};
        pfs_price.reserve(n + 1);
        inclusive_scan(prices.begin(), prices.end(), back_inserter(pfs_price), plus{}, 0ll);
        auto res = pfs_base.back();
        for (const auto i : views::iota(0, n - k + 1)) {
            const auto candidate =
                    pfs_base.back() - (pfs_base[i + k] - pfs_base[i]) + (pfs_price[i + k] - pfs_price[i + k / 2]);
            res = max(res, candidate);
        }
        return res;
    }
};
