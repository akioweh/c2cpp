#include <iterator>
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
    const auto [N, A] = reads<2>();
    const auto arr1 = reads();

    const auto MAX = 2000000000;
    if (A == 0) {
        cout << 1 << endl;
        return;
    }
    if (A == MAX) {
        cout << MAX - 1;
        return;
    }

    auto arr = views::filter(arr1, [A](const auto v) { return v != A; }) | ranges::to<vector>();
    ranges::sort(arr);

    // for (const auto v : arr)
    //     cout << v << ' ';
    // cout << endl;

    const auto m = distance(arr.begin(), ranges::lower_bound(arr, A));


    if (m > arr.size() / 2)
        cout << A - 1 << endl;
    else
        cout << A + 1 << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
