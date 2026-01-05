#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    long long maxMatrixSum(vector<vector<int>> &matrix) {
        auto least = numeric_limits<long long>::max();
        auto n_neg = 0;
        auto tot = 0ll;
        for (const auto &row : matrix) {
            for (const auto val : row) {
                tot += abs(val);
                least = min(least, static_cast<long long>(abs(val)));
                if (val < 0)
                    n_neg++;
            }
        }
        if (n_neg % 2)
            tot -= 2 * least;
        return tot;
    }
};
