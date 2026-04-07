#include <bits/stdc++.h>

using namespace std;


class Robot {
public:
    Robot(int width, int height) : wd(width), ht(height) {}


    void step(int num) {
        fresh = false;
        pos = (pos + num) % ((wd + ht - 2) * 2);
    }

    vector<int> getPos() {
        auto p = pos;
        if (p < wd)
            return {p, 0};
        p -= wd - 1;
        if (p < ht)
            return {wd - 1, p};
        p -= ht - 1;
        if (p < wd)
            return {wd - 1 - p, ht - 1};
        p -= wd - 1;
        return {0, ht - 1 - p};
    }

    string getDir() {
        [[unlikely]] if (fresh)
            return "East";
        else if (pos == 0)
            return "South";
        if (pos < wd)
            return "East";
        if (pos < wd + ht - 1)
            return "North";
        if (pos < wd + ht + wd - 2)
            return "West";
        return "South";
    }


private:
    const int wd;
    const int ht;
    bool fresh = true;
    int pos = 0;
};
