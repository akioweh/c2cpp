#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>> &buildings) {
        auto opens = multiset<int>();
        auto res = vector<vector<int>>();
        auto events = vector<pair<int, int>>();
        events.reserve(buildings.size() * 2);
        for (const auto &v : buildings) {
            const auto l = v[0];
            const auto r = v[1];
            const auto h = v[2];
            events.emplace_back(l, h);
            events.emplace_back(r, -h);
        }
        ranges::sort(events);
        auto prev_x = -1;
        for (const auto &[x, h] : events) {
            if (x != prev_x) {
                if (prev_x != -1) {
                    auto prev_h = 0;
                    if (!opens.empty())
                        prev_h = *opens.crbegin();
                    if (res.empty() || prev_h != res.back()[1])
                        res.push_back(vector{prev_x, prev_h});
                }
                prev_x = x;
            }
            if (h < 0)
                opens.erase(ranges::find(opens, -h));
            else
                opens.insert(h);
        }
        if (res.empty() || res.back()[1] != 0)
            res.push_back(vector{prev_x, 0});

        return res;
    }
};
