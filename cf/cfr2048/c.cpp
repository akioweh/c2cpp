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
    const auto [K, X] = reads<2, ll>();
    auto c = X;
    auto v = (1ll << (K + 1)) - c;
    auto res = vector<char>();
    while (c != v) {
        if (c < v) {
            v -= c;
            c <<= 1;
            res.push_back('1');
        } else {
            c -= v;
            v <<= 1;
            res.push_back('2');
        }
    }
    cout << res.size() << '\n';
    for (const auto v : res | views::reverse)
        cout << v << ' ';
    cout << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
