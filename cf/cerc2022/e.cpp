#pragma GCC optimize("Ofast")

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

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
    auto arr = vector<double>(N);
    for (auto &a : arr)
        cin >> a;
    cin.ignore();
    const auto max_a = *ranges::max_element(arr);
    ranges::transform(arr, arr.begin(), [&](const double v) { return v / max_a; });

    auto best_error = 1e5;
    auto best_mul = -1;
    for (const auto max_x : views::iota(1, 10001) | views::reverse) {
        const auto rn = arr | views::transform([&](const auto a) {
                            const auto x = a * max_x;
                            const auto xi = round(x);
                            return abs(xi - x);
                        });
        const auto err = accumulate(rn.begin(), rn.end(), 0.);
        if (err - 1e-7 < best_error) {
            best_error = err;
            best_mul = max_x;
        }
    }

    for (const auto a : arr)
        cout << static_cast<int>(round(a * best_mul)) << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
