#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;


class Solution {
public:
    int numberOfWays(string corridor) {
        auto res = 1;
        auto p = 1;
        auto cnt = 0;
        for (const auto c : corridor) {
            if (c == 'P') {
                ++p;
            } else {
                if (cnt && cnt % 2 == 0)
                    res = (1ll * res * p) % MOD;
                ++cnt;
                p = 1;
            }
        }
        if (!cnt || cnt % 2)
            return 0;
        return res;
    }
};
