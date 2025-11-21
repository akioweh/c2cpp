#include <cassert>
#include <iterator>
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
    auto arr = reads();
    const auto req = read();

    if (req[0] == '1' || req[N - 1] == '1') {
        cout << -1 << endl;
        return;
    }

    const auto idx_max = distance(arr.begin(), ranges::max_element(arr));
    const auto idx_min = distance(arr.begin(), ranges::min_element(arr));
    if (req[idx_max] == '1' || req[idx_min] == '1') {
        cout << -1 << endl;
        return;
    }

    const auto out = [](const int a, const int b) {
        const auto l = min(a, b);
        const auto r = max(a, b);
        cout << l + 1 << ' ' << r + 1 << '\n';
    };

    cout << 5 << '\n';
    out(0, idx_max);
    out(0, idx_min);
    out(idx_min, idx_max);
    out(idx_min, N - 1);
    out(idx_max, N - 1);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
