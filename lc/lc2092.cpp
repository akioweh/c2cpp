#include <bits/stdc++.h>

using namespace std;


struct DSU {
    vector<int> parent, size;

    DSU(int sz) : parent(from_range, views::iota(0, sz)), size(sz, 1) {}

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (size[x] < size[y])
            swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        return true;
    }

    // unsafe
    void reset(int x) {
        parent[x] = x;
        size[x] = 1;
    }
};


class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>> &meetings, int firstPerson) {
        ranges::sort(meetings, {}, [](const auto &m) { return m[2]; });
        auto groups = meetings | views::chunk_by([&](const auto &a, const auto &b) { return a[2] == b[2]; });
        auto dsu = DSU(n);
        dsu.unite(0, firstPerson);
        for (const auto &group : groups) {
            for (const auto &meeting : group)
                dsu.unite(meeting[0], meeting[1]);
            for (const auto &meeting : group) {
                if (dsu.find(meeting[0]) != dsu.find(0))
                    dsu.reset(meeting[0]);
                if (dsu.find(meeting[1]) != dsu.find(0))
                    dsu.reset(meeting[1]);
            }
        }
        return views::iota(0, n) | views::filter([&dsu](int i) { return dsu.find(i) == dsu.find(0); }) |
                ranges::to<vector>();
    }
};
