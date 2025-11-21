#pragma GCC optimize("Ofast")

#include <vector>
#pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
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
    const auto [N] = reads<1, ll>();
    auto arr = reads<ll>();

    auto sfs = vector(N + 1, 0ll);
    partial_sum(arr.rbegin(), arr.rend(), next(sfs.rbegin()));
    auto L = vector(N, 0ll);
    for (const auto i : views::iota(1ll, N + 1))
        L[i - 1] = i - sfs[i - 1] - i * i;
    auto interv = vector({L.front()});
    for (const auto lv : L | views::drop(1))
        interv.push_back(max(interv.back(), lv));

    auto res = 0ll;
    for (auto i = N; i > 0; --i) {
        const auto l = interv[i - 1];
        const auto r = sfs[i] + i + i * i;
        res = max(res, r + l);
    }
    cout << res + accumulate(arr.begin(), arr.end(), 0ll) << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
