#include <bits/stdc++.h>
#include <limits>

using namespace std;

using ll = long long;


constexpr auto MIN = numeric_limits<ll>::min() - numeric_limits<int>::min();

struct e {
    ll iidle{MIN};
    ll loong{MIN}; // profits - open price
    ll shurt{MIN}; // profits + open price
};


template<class T, class... Ts>
constexpr T vmax(T first, Ts... rest) {
    return (..., (first = max(first, rest)));
}


class Solution {
public:
    long long maximumProfit(vector<int> &prices, int k) {
        const auto n = static_cast<int>(prices.size());
        auto dp = vector(n, vector<e>(k + 1));
        dp[0][0].iidle = 0;
        dp[0][0].loong = -prices[0];
        dp[0][0].shurt = prices[0];
        for (auto i = 1; i < n; ++i) {
            dp[i][0].loong = vmax(dp[i - 1][0].loong, -1ll * prices[i]);
            dp[i][0].shurt = vmax(dp[i - 1][0].shurt, 1ll * prices[i]);
            for (auto j = 1; j <= k; ++j) {
                dp[i][j].iidle = vmax(dp[i - 1][j].iidle, dp[i - 1][j - 1].loong + prices[i],
                                      dp[i - 1][j - 1].shurt - prices[i]);
                dp[i][j].loong = vmax(dp[i - 1][j].loong, dp[i - 1][j].iidle - prices[i]);
                dp[i][j].shurt = vmax(dp[i - 1][j].shurt, dp[i - 1][j].iidle + prices[i]);
            }
        }
        const auto rn = dp.back() | views::transform([](const auto &v) { return v.iidle; });
        return *ranges::max_element(rn);
    }
};
