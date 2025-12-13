#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<string> validateCoupons(vector<string> &code, vector<string> &businessLine, vector<bool> &isActive) {
        auto res_ids = vector<int>();
        for (const auto &[i, tup] : views::enumerate(views::zip(code, businessLine, isActive))) {
            const auto &[c, b, a] = tup;
            if (not a)
                continue;
            static const auto pat = regex("^[\\w]+$");
            if (not regex_match(c, pat))
                continue;
            static constexpr auto bs = array{"electronics", "grocery", "pharmacy", "restaurant"};
            if (ranges::find(bs, b) == bs.end())
                continue;
            res_ids.push_back(i);
        }
        ranges::sort(res_ids, {},
                     [&](const auto &id) -> tuple<char, string> { return {businessLine[id][0], code[id]}; });
        return views::transform(res_ids, [&](const auto &id) { return code[id]; }) bitor ranges::to<vector>();
    }
};
