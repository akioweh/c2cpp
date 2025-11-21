#include <limits>
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
    const auto [N] = reads<1>();
    const auto top = reads();
    const auto bot = reads();

    auto pf_min_top = vector<int>(N);
    auto pf_max_top = vector<int>(N);
    pf_min_top[0] = top[0];
    pf_max_top[0] = top[0];
    for (const auto i : views::iota(1, N)) {
        pf_max_top[i] = max(pf_max_top[i - 1], top[i]);
        pf_min_top[i] = min(pf_min_top[i - 1], top[i]);
    }

    auto sf_min_bot = vector<int>(N);
    auto sf_max_bot = vector<int>(N);
    sf_min_bot[N - 1] = bot[N - 1];
    sf_max_bot[N - 1] = bot[N - 1];
    for (auto i = N - 2; i >= 0; --i) {
        sf_min_bot[i] = min(sf_min_bot[i + 1], bot[i]);
        sf_max_bot[i] = max(sf_max_bot[i + 1], bot[i]);
    }

    auto L = vector(2 * N + 1, vector<int>());
    for (const auto i : views::iota(0, N)) {
        const auto a = min(pf_min_top[i], sf_min_bot[i]);
        const auto b = max(pf_max_top[i], sf_max_bot[i]);
        L[a].push_back(b);
    }

    auto res = 0ll;
    auto cur_min = numeric_limits<int>::max();
    for (auto l = N * 2; l > 0; --l) {
        for (const auto v : L[l])
            cur_min = min(cur_min, v);

        if (cur_min != numeric_limits<int>::max()) {
            res += N * 2 + 1 - cur_min;
        }
    }

    cout << res << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
