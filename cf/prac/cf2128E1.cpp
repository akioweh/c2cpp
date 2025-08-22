#pragma GCC optimize("Ofast")

#include <vector>
// #pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
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
    const auto [N, K] = reads<2>();
    auto arr = reads();
    auto last_l = -1;
    auto last_r = -1;

    const auto check = [&](const auto v) {
        auto ge = vector<int>(N);
        ranges::transform(arr, ge.begin(), [v](const auto u) { return u >= v ? 1 : -1; });
        auto pfs = vector<int>(N + 1);
        pfs[0] = 0;
        partial_sum(ge.begin(), ge.end(), pfs.begin() + 1);
        auto min_pref = 0;
        auto min_pref_l = 0;
        for (const auto r : views::iota(K, N + 1)) {
            const auto new_l = r - K;
            if (pfs[new_l] < min_pref) {
                min_pref = pfs[new_l];
                min_pref_l = new_l;
            }
            if (pfs[r] - min_pref >= 0) {
                last_l = min_pref_l;
                last_r = r;
                return true;
            }
        }
        return false;
    };

    auto rn = views::iota(1, N + 2);
    auto ans = *ranges::partition_point(rn, check) - 1;
    cout << ans << ' ' << last_l + 1 << ' ' << last_r << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
