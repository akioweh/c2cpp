#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool findRotation(vector<vector<int>> &mat, vector<vector<int>> &target) {
        const auto transpose = [](vector<vector<int>> &m) {
            const auto n = static_cast<int>(m.size());
            for (const auto l : views::iota(0, n)) {
                for (const auto i : views::iota(l, n))
                    std::swap(m[l][i], m[i][l]);
            }
        };

        const auto flipx = [](vector<vector<int>> &m) {
            for (auto &vec : m) {
                reverse(vec.begin(), vec.end());
            }
        };

        const auto rotate90 = [&](vector<vector<int>> &m) {
            transpose(m);
            flipx(m);
        };

        const auto eq = [](const vector<vector<int>> &lhs, const vector<vector<int>> &rhs) {
            for (const auto [l, r] : views::zip(lhs, rhs)) {
                if (l != r)
                    return false;
            }
            return true;
        };

        if (eq(mat, target))
            return true;
        for (auto i = int{}; i < 3; ++i) {
            rotate90(mat);
            if (eq(mat, target))
                return true;
        }
        return false;
    }
};
