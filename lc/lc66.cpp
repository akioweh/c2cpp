#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        for (auto &d : digits | views::reverse) {
            if (d < 9) {
                ++d;
                return digits;
            }
            d = 0;
        }
        digits.insert(digits.begin(), 1);
        return digits;
    }
};
