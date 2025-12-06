#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int countCollisions(string directions) {
        while (!directions.empty() && directions.back() == 'R')
            directions.pop_back();
        auto it = directions.begin();
        while (it != directions.end() && *it == 'L')
            ++it;

        return distance(it, directions.end()) - count(it, directions.end(), 'S');
    }
};
