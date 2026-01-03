#include <bits/stdc++.h>
#include <ranges>

using namespace std;

constexpr int MOD = 1e9 + 7;


int make_row(int l, int m, int r) {
    auto v = 0;
    v |= 1 << (l + 6);
    v |= 1 << (m + 3);
    v |= 1 << r;
    return v;
}


class Solution {
public:
    int numOfWays(int n) {
        auto rs = vector<int>();
        constexpr auto vs = array{0, 1, 2};
        for (const auto [v1, v2, v3] : views::cartesian_product(vs, vs, vs)) {
            if (v1 == v2 || v2 == v3)
                continue;
            rs.push_back(make_row(v1, v2, v3));
        }
        const auto m = static_cast<int>(rs.size());
        auto res = vector(m, 1ll);
        while (--n) {
            auto nxt = vector(m, 0ll);
            for (const auto [i, r] : views::enumerate(rs)) {
                for (const auto [j, s] : views::enumerate(rs)) {
                    if (r & s)
                        continue;
                    nxt[j] += res[i];
                    if (nxt[j] >= MOD)
                        nxt[j] -= MOD;
                }
            }
            res = std::move(nxt);
        }
        return accumulate(res.begin(), res.end(), 0ll) % MOD;
    }
};
