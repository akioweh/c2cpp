#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxWalls(vector<int> &robots, vector<int> &distance, vector<int> &walls) {
        const auto n = static_cast<int>(robots.size());
        const auto wn = static_cast<int>(walls.size());
        auto idxs = views::iota(0, n) | ranges::to<vector>();
        ranges::sort(idxs, {}, [&](int i) { return robots[i]; });
        ranges::sort(walls);

        // left <- best score if last robot fired left
        // right <- best score if last robot fired right
        // last_reach <- right-most destroyed wall if last robot shot rightwards
        auto left = 0;
        auto right = 0;
        auto last_reach = 0;

        // index of next wall AFTER last robot
        auto wall_idx = 0;

        for (const auto [i, idx] : views::enumerate(idxs)) {
            const auto pos = robots[idx];
            const auto reach = distance[idx];
            const auto l_ = i ? robots[idxs[i - 1]] + 1 : walls.front();
            const auto r_ = i < n - 1 ? robots[idxs[i + 1]] - 1 : walls.back();
            const auto l = max(l_, pos - reach);
            const auto r = min(r_, pos + reach);

            // count left walls
            auto walls_left = 0;
            auto walls_overlap = 0; // double-counted walls if last right now left
            auto wdx = wall_idx;
            while (wdx < wn && walls[wdx] < l)
                ++wdx;
            while (wdx < wn && walls[wdx] <= pos) {
                ++walls_left;
                if (walls[wdx] <= last_reach)
                    ++walls_overlap;
                ++wdx;
            }
            // count right walls
            wall_idx = wdx;
            auto walls_right = (wdx && walls[wdx - 1] == pos) ? 1 : 0;
            while (wdx < wn && walls[wdx] <= r) {
                ++walls_right;
                ++wdx;
            }

            auto new_left = max(left + walls_left, right + walls_left - walls_overlap);
            auto new_right = max(left, right) + walls_right;
            last_reach = r;
            left = new_left;
            right = new_right;
        }

        return max(left, right);
    }
};
