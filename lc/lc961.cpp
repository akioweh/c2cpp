#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int repeatedNTimes(vector<int> &nums) {
        auto seen = vector(10001, false);
        for (const auto v : nums) {
            if (seen[v])
                return v;
            seen[v] = true;
        }
        return -1;
    }
};
