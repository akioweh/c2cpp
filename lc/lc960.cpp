#include <algorithm>
#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int minDeletionSize(vector<string> &strs) {
        auto m = static_cast<int>(strs.front().size());
        auto max_len = vector<pair<vector<char>, int>>();
        for (const auto i : views::iota(0, m)) {
            const auto cur = strs |
                    views::transform(bind_back(static_cast<char &(string::*) (size_t)>(&string::operator[]), i)) |
                    ranges::to<vector>();
            auto max_pre = 0;
            auto existing = max_len.end();
            for (auto it = max_len.begin(); it != max_len.end(); ++it) {
                const auto &[o, c] = *it;
                if (o == cur)
                    existing = it;
                if (ranges::all_of(views::zip(o, cur), [](const auto &p) { return get<0>(p) <= get<1>(p); }))
                    max_pre = max(max_pre, c);
            }
            if (existing == max_len.end())
                max_len.emplace_back(cur, max_pre + 1);
            else
                existing->second = max(existing->second, max_pre + 1);
        }
        return m - ranges::max_element(max_len, {}, &pair<vector<char>, int>::second)->second;
    }
};
