#include <stdexcept>
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

    auto even1 = -1;
    auto even2 = -1;
    for (const auto [i, v] : views::enumerate(arr)) {
        if (v % 2)
            continue;
        if (even1 == -1) {
            even1 = i;
            continue;
        }
        even2 = i;
        break;
    }

    if (even2 != -1) {
        cout << arr[even1] << ' ' << arr[even2] << endl;
        return;
    }

    auto odds = vector<int>();
    for (const auto v : arr) {
        if (v % 2)
            odds.push_back(v);
    }

    if (odds.size() > 30) {
        for (const auto [x, y] : views::pairwise(odds)) {
            if (y < 2 * x) {
                cout << x << ' ' << y << endl;
                return;
            }
        }
        throw runtime_error("wtf");
    }
    for (const auto i : views::iota(0ull, odds.size() - 1)) {
        const auto x = odds[i];
        for (const auto j : views::iota(i + 1, odds.size())) {
            const auto y = odds[j];
            if ((y % x) % 2 == 0) {
                cout << x << ' ' << y << endl;
                return;
            }
        }
    }
    if (even1 == -1) {
        cout << "-1" << endl;
        return;
    }
    const auto y = arr[even1];
    for (const auto i : views::iota(0, even1)) {
        const auto x = arr[i];
        if ((y % x) % 2 == 0) {
            cout << x << ' ' << y << endl;
            return;
        }
    }
    cout << "-1" << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
