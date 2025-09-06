#pragma GCC optimize("Ofast")

#include <vector>
#pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
#include <functional>
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
    const auto [V, E] = reads<2>();
    // src == 0; dst == 1.

    auto graph = vector(V, vector<pair<int, int>>());
    for (const auto _ : views::iota(0, E)) {
        const auto [u, v, w] = reads<3>();
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    auto dist = vector(V, numeric_limits<ll>::max());
    auto par = vector(V, -1);
    auto pq = priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>>();
    dist[1] = 0;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u])
            continue;
        for (const auto [v, w] : graph[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                par[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }

    for (const auto v : views::iota(0, V)) {
        if (v == 1)
            continue;
        auto it = ranges::find_if(graph[v], [&](const auto pi) { return pi.first == par[v]; });
        if (it == graph[v].end())
            cout << "wtf " << v << ' ' << par[v] << endl;
        graph[v].erase(it);
    }

    auto par2 = vector(V, -1);
    auto visited = vector(V, false);
    auto visiting = vector(V, false);

    const function<bool(int, int)> pathable_from = [&](const int u, const int p) {
        visiting[u] = true;
        par2[u] = p;
        if (u == 1)
            return true;
        for (const auto &[v, _] : graph[u]) {
            if (visited[v] || visiting[v])
                continue;
            if (pathable_from(v, u))
                return true;
        }
        visiting[u] = false;
        visited[u] = true;
        return false;
    };

    if (!pathable_from(0, -1)) {
        cout << "impossible" << endl;
        return;
    }

    auto path = vector<int>();
    for (auto cur = 1; cur != -1; cur = par2[cur])
        path.push_back(cur);

    cout << path.size() << ' ';
    for (const auto v : path | views::reverse)
        cout << v << ' ';
    cout << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
