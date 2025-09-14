#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;


string read() {
    string line;
    getline(cin, line);
    return line;
}


template<typename T = int>
vector<T> reads() {
    istringstream iss(read());
    return {istream_iterator<T>(iss), istream_iterator<T>()};
}


template<size_t N, typename T = int, bool validate = true>
array<T, N> reads() {
    array<T, N> arr;
    istringstream iss(read());
    auto issv = views::istream<T>(iss) | views::take(N);
    const auto r = ranges::copy(issv, arr.begin());
    if (validate) {
        if (iss.fail() && !iss.eof())
            throw runtime_error("reads() fail: parse error");
        if (r.in.base() != default_sentinel_t{})
            throw runtime_error("reads() fail: excess elements");
        if (r.out != arr.end())
            throw runtime_error("reads() fail: not enough elements");
    }
    return arr;
}


struct pair_hash {
    size_t operator()(const pair<int, int> &p) const { return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1); }
};


void solve() {
    const auto [N, Q] = reads<2>();

    unordered_map<string, int> names;
    auto idx = 0;
    unordered_map<pair<int, int>, double, pair_hash> ratios; // edge weights

    int vi;
    string vs1;
    string vs2;
    string _;
    double vd;
    for (const auto i : views::iota(0, N)) {
        cin >> vi >> vs1 >> _ >> vd >> vs2;
        if (!names.contains(vs1))
            names[vs1] = idx++;
        if (!names.contains(vs2))
            names[vs2] = idx++;
        const auto a = names[vs1];
        const auto b = names[vs2];
        ratios[{a, b}] = vd;
        ratios[{b, a}] = 1. / vd;
    }

    const auto M = idx;
    auto adj = vector(M, vector<pair<int, double>>());
    for (const auto &[p, w] : ratios) {
        const auto &[u, v] = p;
        adj[u].emplace_back(v, w);
    }

    auto dists = vector(M, vector(M, -1.));
    for (const auto src : views::iota(0, M)) {
        auto &dist = dists[src];
        dist[src] = 1.;
        auto q = queue<int>({src});
        while (!q.empty()) {
            const auto u = q.front();
            q.pop();
            for (const auto [v, w] : adj[u]) {
                if (dist[v] != -1.)
                    continue;
                dist[v] = dist[u] * w;
                q.push(v);
            }
        }
    }

    for (const auto i : views::iota(0, Q)) {
        cin >> vd >> vs1 >> _ >> vs2;
        const auto r = dists[names[vs1]][names[vs2]];
        if (r == -1.) {
            cout << "impossible\n";
            continue;
        }
        cout << scientific << setprecision(numeric_limits<double>::max_digits10) << vd * r << '\n';
    }

    cin.ignore();
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
