#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool judgeCircle(string moves) {
        auto x = 0;
        auto y = 0;
        for (const auto c : moves) {
            switch (c) {
                case 'U':
                    ++y;
                    break;
                case 'L':
                    --x;
                    break;
                case 'R':
                    ++x;
                    break;
                case 'D':
                    --y;
                    break;
            }
        }
        return x == 0 && y == 0;
    }
};
