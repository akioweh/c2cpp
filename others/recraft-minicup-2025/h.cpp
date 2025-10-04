#include <functional>
#include <numeric>
#pragma GCC optimize("Ofast")

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
    const auto [V, E] = reads<2>();
    auto graph = vector(V, vector<int>());
    for (const auto _ : views::iota(0, E)) {
        auto [u, v] = reads<2>();
        --u;
        --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto seen = vector(V, false);
    auto sizes = vector<int>();

    const function<int(int)> dfs = [&](const auto u) {
        seen[u] = true;
        auto res = 1;
        for (const auto v : graph[u]) {
            if (seen[v])
                continue;
            res += dfs(v);
        }
        return res;
    };

    for (const auto u : views::iota(0, V)) {
        if (seen[u])
            continue;
        sizes.push_back(dfs(u));
    }

    auto numerator = 0ll;
    for (const auto cnt : sizes) {
        numerator += static_cast<ll>(cnt) * (V - cnt);
    }
    auto denom = static_cast<ll>(V) * (V - 1);
    const auto g = gcd(numerator, denom);
    denom /= g;
    numerator /= g;
    numerator = denom - numerator;
    cout << numerator << ' ' << denom << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
