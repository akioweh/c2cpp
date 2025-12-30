#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>> &grid) {
        const auto n = static_cast<int>(grid.size());
        const auto m = static_cast<int>(grid.front().size());

        const auto check = [&](const int y, const int x) {
            auto seen = array<bool, 10>{};
            for (auto i = y; i < y + 3; ++i) {
                for (auto j = x; j < x + 3; ++j) {
                    const auto v = grid[i][j];
                    if (v < 1 || v > 9)
                        return false;
                    if (seen[v])
                        return false;
                    seen[v] = true;
                }
            }
            const auto target = grid[y][x] + grid[y][x + 1] + grid[y][x + 2];
            // rows
            for (auto i = y; i < y + 3; ++i) {
                if (grid[i][x] + grid[i][x + 1] + grid[i][x + 2] != target)
                    return false;
            }
            // cols
            for (auto j = x; j < x + 3; ++j) {
                if (grid[y][j] + grid[y + 1][j] + grid[y + 2][j] != target)
                    return false;
            }
            // diagonals
            if (grid[y][x] + grid[y + 1][x + 1] + grid[y + 2][x + 2] != target)
                return false;
            if (grid[y][x + 2] + grid[y + 1][x + 1] + grid[y + 2][x] != target)
                return false;
            return true;
        };

        auto res = 0;
        for (auto i = 0; i + 2 < n; ++i) {
            for (auto j = 0; j + 2 < m; ++j) {
                if (check(i, j))
                    ++res;
            }
        }
        return res;
    }
};
