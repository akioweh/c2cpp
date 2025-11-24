#include <cmath>
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
    auto arr = vector<tuple<int, int, int>>();
    arr.reserve(N);
    for (const auto _ : views::iota(0, N))
        arr.emplace_back(reads<3>());

    const auto dist = [](const auto x1, const auto y1, const auto x2, const auto y2) {
        return hypot(x1 - x2, y1 - y2);
    };

    for (const auto [i, t3] : views::enumerate(arr)) {
        const auto &[x, y, h] = t3;
        auto min_sep = static_cast<double>(h);
        for (const auto j : views::iota(0, N)) {
            if (j == i || get<2>(arr[j]) < h)
                continue;
            min_sep = min(min_sep, dist(x, y, get<0>(arr[j]), get<1>(arr[j])));
        }
        cout << static_cast<int>(floor(min_sep)) << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
