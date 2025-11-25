#include <numeric>
#include <vector>

using namespace std;


struct DSU {
    vector<int> par;
    vector<int> size;

    DSU(int n) : par(n), size(n, 1) { ranges::iota(par, 0); }

    int find(const int x) {
        if (par[x] != x)
            par[x] = find(par[x]);
        return par[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;

        if (size[a] < size[b])
            swap(a, b);
        par[b] = a;
        size[a] += size[b];
        return true;
    }
};
