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
    const auto [X, Y, K] = reads<3, ll>();
    const ll MAX = 1e12;
    if (Y == 1) {
        cout << -1 << endl;
        return;
    }
    if (K < Y) {
        cout << K << endl;
        return;
    }

    auto cur = K;
    auto i = X;
    while (i > 0 && cur <= MAX) {
        const auto delta = (cur - 1) / (Y - 1);
        const auto nxt = (delta + 1) * (Y - 1) + 1;
        const auto dist = nxt - cur;
        const auto iters = (dist + delta - 1) / delta;
        cur += min(iters, i) * delta;
        i -= min(iters, i);
    }

    cout << (cur > MAX ? -1 : cur) << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
