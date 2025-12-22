#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int minDeletionSize(vector<string> &strs) {
        const auto n = static_cast<int>(strs.size());
        const auto m = static_cast<int>(strs[0].size());
        auto res = 0;
        auto msk = vector(n, true);
        for (auto i = 0; i < m; ++i) {
            auto new_msk = msk;
            auto good = true;
            for (auto j = 1; j < n; ++j) {
                if (!msk[j])
                    continue;
                const auto cmp = strs[j][i] <=> strs[j - 1][i];
                if (cmp < 0) {
                    good = false;
                    ++res;
                    break;
                }
                if (cmp != 0)
                    new_msk[j] = false;
            }
            if (good)
                msk = std::move(new_msk);
        }
        return res;
    }
};
