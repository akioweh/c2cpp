#include <algorithm>
#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int minimumBoxes(vector<int> &apple, vector<int> &capacity) {
        auto tot = accumulate(apple.begin(), apple.end(), 0);
        ranges::sort(capacity, greater{});
        auto res = 0;
        for (const auto v : capacity) {
            if (tot <= 0)
                break;
            ++res;
            tot -= v;
        }
        return res;
    }
};
