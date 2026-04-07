#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int numDistinct(string s, string t) {
        // dp[i][j] = #sub-seqs of t[:j] in s ending on s[i-1]
        // dp[i][j] = 0 if s[i-1] != t[j-1] else sum(dp[k][j-1] for k in range(i))
        // iterate for all j
        // then all this iterated for all i
        // ans = sum(dp[i+1][len(t)] for i in range(len(s)))

        const auto n = static_cast<int>(s.length());
        const auto m = static_cast<int>(t.length());

        auto dp = vector(n + 1, vector(m + 1, 0u));
        dp[0][0] = 1;
        // pfs[j] = sum(dp[i][j] for i in 0..)
        auto pfs = vector(m + 1, 0u);

        for (const auto i : views::iota(1, n + 1)) {
            for (const auto j : views::iota(1, min(m, i) + 1)) {
                // pfs should be a sum of [0, i)
                // this will overflow but is ok :)
                pfs[j - 1] += dp[i - 1][j - 1];
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = pfs[j - 1];
            }
        }

        auto res = 0;
        for (const auto i : views::iota(1, n + 1))
            res += dp[i][m];
        return res;
    }
};
