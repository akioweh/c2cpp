#include <vector>

using namespace std;


class Solution {
public:
    int maxCandies(
        vector<int> &status,
        vector<int> &candies,
        vector<vector<int>> &keys,
        vector<vector<int>> &containedBoxes,
        vector<int> &initialBoxes
    ) {
        const auto n = status.size();
        long long ans = 0;
        vector<int> can_open;
        vector lone_key(n, false);  // has key but not box
        vector lone_box(n, false);  // has box (is closed) but no key
        vector seen(n, false);  // are the inputs stupid?
        for (const auto box : initialBoxes) {
            if (status[box])
                can_open.push_back(box);
            else
                lone_box[box] = true;
        }
        while (!can_open.empty()) {
            const auto box = can_open.back();
            can_open.pop_back();
            if (seen[box]) continue;
            ans += candies[box];
            seen[box] = true;
            for (const auto k : keys[box]) {
                if (lone_box[k])
                    can_open.push_back(k);
                else
                    lone_key[k] = true;
            }
            for (const auto contained : containedBoxes[box]) {
                if (status[contained]) {
                    can_open.push_back(contained);
                } else {
                    if (lone_key[contained])
                        can_open.push_back(contained);
                    else
                        lone_box[contained] = true;
                }
            }
        }
        return ans;
    }
};
