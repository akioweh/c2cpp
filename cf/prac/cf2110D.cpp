// #pragma GCC optimize("Ofast,unroll-loops,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


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


template<size_t N, typename T = int>
array<T, N> reads() {
    array<T, N> arr{};
    istringstream iss(read());
    auto r = ranges::copy(
        views::istream<T>(iss) | views::take(N),
        arr.begin()
    );
    if (r.out != arr.end()) { throw runtime_error("not enough elements"); }
    return arr;
}


void solve() {
    const auto [N, M] = reads<2>();
    const auto bats = reads();
    vector graph(N, vector<pair<int, int>>());
    auto max_w = 0;
    for (auto i = 0; i < M; ++i) {
        auto [u, v, w] = reads<3>();
        --u; --v;
        graph[u].emplace_back(v, w);
        max_w = max(max_w, w);
    }

    auto check = [&](const int max_bats) -> bool {
        vector dp(N, -1);  // max greedy amount
        dp[0] = min(bats[0], max_bats);
        for (auto u = 0; u < N; ++u) {
            for (const auto &[v, w] : graph[u]) {
                if (dp[u] < w)
                    continue;
                dp[v] = max(dp[v], min(dp[u] + bats[v], max_bats));
            }
        }
        return dp[N - 1] >= 0;
    };

    const auto r = views::iota(0, max_w + 1);
    const auto it = ranges::lower_bound(r, false, equal_to(), check);
    cout << (it != r.end() ? *it : -1) << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
