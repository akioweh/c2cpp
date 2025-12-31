#include <bits/stdc++.h>

using namespace std;


struct DSU {
    vector<int> par;
    vector<int> sz;

    DSU(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }

    int find(int x) {
        if (par[x] != x)
            par[x] = find(par[x]);
        return par[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (sz[x] > sz[y])
            swap(x, y);
        par[x] = y;
        sz[y] += sz[x];
        return true;
    }
};


class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>> &cells) {
        const auto L = row * col;
        const auto R = L + 1;
        auto dsu = DSU(row * col + 2);
        auto filled = vector(row * col, false);

        const auto id = [=](const int r, const int c) { return (r - 1) * col + c - 1; };

        const auto add = [&](const int r, const int c) {
            if (c == 1)
                dsu.unite(id(r, c), L);
            if (c == col)
                dsu.unite(id(r, c), R);
            for (const auto [dx, dy] : views::cartesian_product(array{-1, 0, 1}, array{-1, 0, 1})) {
                if (dx == 0 && dy == 0)
                    continue;
                const auto nr = r + dy;
                const auto nc = c + dx;
                if (nr <= 0 || nr > row || nc <= 0 || nc > col)
                    continue;
                if (!filled[id(nr, nc)])
                    continue;
                dsu.unite(id(r, c), id(nr, nc));
            }
            filled[id(r, c)] = true;
        };

        for (const auto [i, coord] : views::enumerate(cells)) {
            add(coord[0], coord[1]);
            if (dsu.find(L) == dsu.find(R))
                return i;
        }
        return cells.size();
    }
};
