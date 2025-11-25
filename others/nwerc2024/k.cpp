#pragma GCC optimize("Ofast")

#include <vector>
#pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
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
    const auto [V, E, K] = reads<3>();
    auto adj = vector(V, vector<pair<int, int>>());
    for (auto _ = 0; _ < E; ++_) {
        auto [u, v, w] = reads<3>();
        --u;
        --v;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    auto prob = vector(V, 0.);
    auto has = vector<int>();
    has.reserve(K);
    for (auto _ = 0; _ < K; ++_) {
        int i;
        double p;
        cin >> i >> p;
        cin.ignore();
        --i;
        prob[i] = p;
        has.push_back(i);
    }
    if (!ranges::any_of(prob, [](int p) { return p == 1.; })) {
        cout << "impossible" << endl;
        return;
    }

    const auto dij = [&](const auto src) {
        auto dist = vector(V, numeric_limits<ll>::max());
        dist[src] = 0;
        auto pq = priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>>();
        pq.emplace(0, src);
        while (!pq.empty()) {
            const auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u])
                continue;
            for (const auto [v, w] : adj[u]) {
                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    pq.emplace(d + w, v);
                }
            }
        }
        return dist;
    };

    auto dist_h = dij(0);
    auto dist_u = dij(V - 1);

    const auto cost = views::iota(0, V) | views::transform([&](const auto u) { return dist_h[u] + dist_u[u]; }) |
                      ranges::to<vector>();
    ranges::sort(has, {}, [&](const auto i) { return cost[i]; });

    auto cur = 1.;
    auto res = 0.;
    for (const auto u : has) {
        res += prob[u] * cur * cost[u];
        cur *= (1. - prob[u]);
    }

    cout << scientific << setprecision(numeric_limits<double>::max_digits10) << res << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
