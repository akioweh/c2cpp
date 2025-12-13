#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>> &events) {
        auto new_events = vector<tuple<bool, int, string>>();
        new_events.reserve(events.size());
        for (const auto &vec : events)
            new_events.emplace_back(vec[0][0] == 'M', stoi(vec[1]), vec[2]);
        ranges::sort(new_events, {}, [](const auto &tup) { return pair{get<1>(tup), get<0>(tup)}; });
        auto online = vector(numberOfUsers, 0);
        auto alls = 0;
        auto res = vector(numberOfUsers, 0);
        for (const auto &[typ, time, ss] : new_events) {
            if (typ) {
                if (ss == "ALL") {
                    ++alls;
                } else if (ss == "HERE") {
                    for (const auto [id, t] : views::enumerate(online)) {
                        if (t > time)
                            continue;
                        ++res[id];
                    }
                } else {
                    auto iss = istringstream(ss);
                    string s;
                    while (iss >> s) {
                        const auto id = stoi(s.substr(2));
                        ++res[id];
                    }
                }
            } else {
                const auto id = stoi(ss);
                online[id] = time + 60;
            }
        }
        for (auto &v : res)
            v += alls;
        return res;
    }
};
