#pragma GCC optimize("Ofast,unroll-loops,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


template<typename T = int>
vector<T> reads() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    return {istream_iterator<T>(iss), istream_iterator<T>()};
}


template<size_t N, typename T = int>
array<T, N> reads() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    array<T, N> arr{};
    auto r = ranges::copy(
        views::istream<T>(iss) | views::take(N),
        arr.begin()
    );
    if (r.out != arr.end()) { throw runtime_error("not enough elements"); }
    return arr;
}


void solve() {
    auto [a, b, c] = reads<3>();
    c -= 2 * b - a;
    if (c >= 0 && c % 3 == 0)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [T] = reads<1>();
    while (T--) {
        solve();
    }
    return 0;
}
