#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>> &buildings) {
        auto xs = vector(n + 1, pair{n + 1, 0});
        auto ys = vector(n + 1, pair{n + 1, 0});
        for (const auto &vec : buildings) {
            const auto x = vec[0];
            const auto y = vec[1];
            auto &xx = xs[x];
            auto &yy = ys[y];
            xx.first = min(xx.first, y);
            xx.second = max(xx.second, y);
            yy.first = min(yy.first, x);
            yy.second = max(yy.second, x);
        }
        auto res = 0;
        for (const auto &vec : buildings) {
            const auto x = vec[0];
            const auto y = vec[1];
            auto &xx = xs[x];
            auto &yy = ys[y];
            if (y > xx.first && y < xx.second && x > yy.first && x < yy.second)
                ++res;
        }
        return res;
    }
};
