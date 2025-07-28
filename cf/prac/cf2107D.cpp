// #pragma GCC optimize("no-stack-protector,unroll-loops,O3,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


template<typename T = int>
vector<T> reads() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    return {istream_iterator<T>(iss), istream_iterator<T>()};
}


template<size_t N, typename T = int>
array<T, N> reads() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    array<T, N> arr{};
    auto r = ranges::copy(
        views::istream<T>(iss) | views::take(N),
        arr.begin()
    );
    if (r.out != arr.end()) { throw runtime_error("not enough elements"); }
    return arr;
}


template<bool WriteState = false>
pair<int, int> bfs_furthest(
    const vector<vector<int>> &graph,
    vector<bool> &mask,
    vector<bool> &visited,
    vector<int> &parent,
    const int source
) {
    int dist = 0;
    vector cur_vs = {make_pair(source, -1)};
    if (WriteState) parent[source] = -1;  // once again, program termination *would* be nice
    while (true) {
        vector<pair<int, int>> next_vs;
        for (const auto [u, prev] : cur_vs) {
            if (WriteState) visited[u] = true;
            for (const auto v : graph[u]) {
                if (v == prev || !mask[v]) continue;
                next_vs.emplace_back(v, u);
                if (WriteState) parent[v] = u;
            }
        }
        if (next_vs.empty()) break;
        dist++;
        cur_vs = move(next_vs);
    }
    return {*ranges::max_element(cur_vs | views::elements<0>), dist};
}


tuple<int, int, int> extract_diameter(
    const vector<vector<int>> &graph,
    vector<bool> &mask,
    vector<bool> &visited,
    vector<int> &parent,
    const int u
) {
    const auto a = bfs_furthest(graph, mask, visited, parent, u).first;
    const auto [b, d] = bfs_furthest<true>(graph, mask, visited, parent, a);
    for (auto w = b; w > 0; w = parent[w])
        mask[w] = false;
    return {d, max(a, b), min(a, b)};
}


void solve() {
    auto [N] = reads<1>();
    auto graph = vector(N + 1, vector<int>());
    for (auto i = N - 1; i--;) {
        auto [u, v] = reads<2>();
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    // graph is a tree
    vector mask(N + 1, true), visited(N + 1, false);
    mask[0] = false;  // would be nice for the program to terminate, yk.
    vector parent(N + 1, -1);
    vector<tuple<int, int, int>> ans;
    for (;ranges::any_of(mask, identity()); visited.assign(N + 1, false)) {
        for (auto u = 1; u <= N; u++) {
            if (visited[u] || !mask[u]) continue;
            auto res = extract_diameter(graph, mask, visited, parent, u);
            get<0>(res)++;  // we want n-vertices
            ans.push_back(res);
        }
    }
    ranges::sort(ans, greater<tuple<int, int, int>>{});
    for (const auto [d, a, b] : ans)
        cout << d << ' ' << a << ' ' << b << ' ';
    cout << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [T] = reads<1, int>();
    while (T--) {
        solve();
    }
    return 0;
}
