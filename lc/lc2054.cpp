#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int maxTwoEvents(vector<vector<int>> &events) {
        auto e = vector<tuple<int, int, int>>(); // t, typ, idx
        e.reserve(events.size() * 2);
        for (const auto &[i, ev] : views::enumerate(events)) {
            e.emplace_back(ev[0], 0, i);
            e.emplace_back(ev[1], 1, i);
        }
        ranges::sort(e);
        auto res = 0;
        auto cur_max = 0;
        for (const auto &[t, typ, idx] : e) {
            if (typ == 0)
                res = max(res, cur_max + events[idx][2]);
            else
                cur_max = max(cur_max, events[idx][2]);
        }
        return res;
    }
};
