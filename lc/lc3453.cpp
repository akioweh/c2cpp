#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    double separateSquares(vector<vector<int>> &squares) {

        const auto calc = [](const double y, const vector<int> &sq) -> pair<double, double> {
            const auto yl = sq[1];
            const auto l = sq[2];
            const auto yr = yl + l;
            if (yr < y)
                return {0., 1. * l * l};
            if (yl > y)
                return {1. * l * l, 0.};
            return {abs(y - yr) * l, abs(y - yl) * l};
        };

        const auto check = [&](const double y) {
            auto above = 0.;
            auto below = 0.;
            for (const auto &sq : squares) {
                const auto [a, b] = calc(y, sq);
                above += a;
                below += b;
            }
            return above > below;
        };

        auto l = 0.;
        auto r = 1e10;
        for (auto _ = 0; _ < 100; ++_) {
            const auto m = (l + r) / 2;
            if (check(m))
                l = m;
            else
                r = m;
        }
        return (l + r) / 2;
    }
};
