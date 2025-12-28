#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int countNegatives(vector<vector<int>> &grid) {
        const auto n = static_cast<int>(grid.size());
        const auto m = static_cast<int>(grid.front().size());
        auto res = 0;
        auto x = 0;
        auto y = n;
        while (--y >= 0) {
            while (x < m && grid[y][x] >= 0)
                ++x;
            res += m - x;
        }
        return res;
    }
};
