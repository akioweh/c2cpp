#pragma GCC optimize("Ofast")

#include <queue>
#include <unordered_set>
#include <vector>
#pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>

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


void solve() {
    const auto [N] = reads<1>();
    auto stars = vector<pair<int, int>>(N);
    for (auto &star : stars)
        star = reads<2>();

    const auto M = (N * 2) + 1;
    auto idx = N; // larger idx == younger
    auto sdistsq = vector(M, vector(M, 0ll));
    auto size = vector(M, 0);
    auto exists = vector<bool>(M, false);
    auto existing = unordered_set<int>(); // (i for i, b in enumerate(exists) if b)

    for (const auto u : views::iota(0, N)) {
        existing.insert(u);
        exists[u] = true;
        size[u] = 1;
    }

    using cand = pair<int, int>; // u, v; u < v
    const auto comp = [&](const cand pa, const cand pb) { // true if b comes before a
        const auto [au, av] = pa;
        const auto [bu, bv] = pb;
        const auto da = static_cast<double>(sdistsq[au][av]) / (static_cast<double>(size[au]) * size[av]);
        const auto db = static_cast<double>(sdistsq[bu][bv]) / (static_cast<double>(size[bu]) * size[bv]);
        return tuple{da, au, av} > tuple{db, bu, bv};
    };
    auto pq = priority_queue<cand, vector<cand>, decltype(comp)>(comp);

    for (const auto u : views::iota(0, N - 1)) {
        for (const auto v : views::iota(u + 1, N)) {
            const auto [ux, uy] = stars[u];
            const auto [vx, vy] = stars[v];
            const auto dx = vx - ux;
            const auto dy = vy - uy;
            sdistsq[u][v] = sdistsq[v][u] = (dx * dx) + (dy * dy);
            pq.emplace(u, v);
        }
    }

    const auto merge = [&](const int u, const int v) {
        existing.erase(u);
        existing.erase(v);
        exists[u] = false;
        exists[v] = false;
        const auto ni = idx++;
        size[ni] = size[u] + size[v];
        for (const auto w : existing) {
            sdistsq[ni][w] = sdistsq[w][ni] = sdistsq[u][w] + sdistsq[v][w];
            pq.emplace(w, ni);
        }
        existing.insert(ni);
        exists[ni] = true;
        return size[ni];
    };

    while (!pq.empty()) {
        const auto [u, v] = pq.top();
        pq.pop();
        if (!exists[u] || !exists[v])
            continue;
        cout << merge(u, v) << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
