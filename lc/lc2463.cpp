#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;
using ll = long long;


class Solution {
public:
    long long minimumTotalDistance(vector<int> &robot, vector<vector<int>> &factory) {
        const auto n = static_cast<int>(robot.size());
        const auto m = static_cast<int>(factory.size());
        ranges::sort(robot);
        ranges::sort(factory, {}, [](const auto &vec) { return vec[0]; });

        auto row = vector(n + 1, numeric_limits<long long>::max() / 2); // row[i] = ans for robot[:i]
        row[0] = 0;
        for (const auto j : views::iota(1, m + 1)) {
            const auto f_pos = static_cast<long long>(factory[j - 1][0]);
            const auto f_cap = factory[j - 1][1];
            auto new_row = row;
            for (const auto i : views::iota(1, n + 1)) {
                auto new_dist_sum = 0ll;
                for (const auto k : views::iota(1, min(f_cap, i) + 1)) {
                    new_dist_sum += abs(f_pos - robot[i - k]);
                    new_row[i] = min(new_row[i], row[i - k] + new_dist_sum);
                }
            }
            row = std::move(new_row);
        }

        return row.back();
    }
};
