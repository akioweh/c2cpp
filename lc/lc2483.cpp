#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int bestClosingTime(string customers) {
        const auto n = static_cast<int>(customers.size());
        const auto proj = customers | views::transform([](const char c) -> int { return c == 'Y'; });
        auto pfs = vector<int>({0}); // number of Ys
        pfs.reserve(n + 1);
        inclusive_scan(proj.begin(), proj.end(), back_inserter(pfs));
        auto min_pen = numeric_limits<int>::max();
        auto res = -1;
        for (const auto i : views::iota(0, n + 1)) {
            const auto cur_pen = i - pfs[i] + (pfs.back() - pfs[i]);
            if (cur_pen < min_pen) {
                min_pen = cur_pen;
                res = i;
            }
        }
        return res;
    }
};
