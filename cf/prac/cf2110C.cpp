// #pragma GCC optimize("Ofast,unroll-loops,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


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


template<size_t N, typename T = int>
array<T, N> reads() {
    array<T, N> arr{};
    istringstream iss(read());
    auto r = ranges::copy(
        views::istream<T>(iss) | views::take(N),
        arr.begin()
    );
    if (r.out != arr.end()) { throw runtime_error("not enough elements"); }
    return arr;
}


void solve() {
    const auto [N] = reads<1>();
    auto d = reads();
    vector<int> t(N), b(N);
    for (auto &&[r, l] : views::zip(t, b))
        cin >> l >> r;
    cin.ignore();

    for (auto &&[t2_, d_] : views::zip(t | views::reverse | views::pairwise , d | views::reverse)) {
        auto &&[t_, tp_] = t2_;
        tp_ = min(t_ - (d_ == 1), tp_);
    }

    auto cur_h = 0;
    for (auto &&[d_, b_, t_] : views::zip(d, b, t)) {
        if (d_ == -1)
            d_ = cur_h + 1 <= t_;
        cur_h += d_;
        if (cur_h < b_ || cur_h > t_) {
            cout << -1 << endl;
            return;
        }
    }

    for (const auto v : d)
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
