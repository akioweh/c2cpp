#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int closestTarget(vector<string> &words, string target, int startIndex) {
        const auto n = static_cast<int>(words.size());
        for (const auto d : views::iota(0, n / 2 + 1)) {
            if (words[(startIndex + d) % n] == target || words[(startIndex - d + n) % n] == target)
                return d;
        }
        return -1;
    }
};
