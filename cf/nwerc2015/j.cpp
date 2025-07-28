// #pragma GCC optimize("Ofast,unroll-loops,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <iostream>
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
    auto r = ranges::copy(views::istream<T>(iss) | views::take(N), arr.begin());
    if (r.out != arr.end()) {
        throw runtime_error("not enough elements");
    }
    return arr;
}


int dec(const int v) {
    int res = 0;
    int prevb = 0;
    for (auto i = 0; i < 8; ++i) {
        int b = (v >> i) & 1;
        int d = b ^ prevb;
        res |= d << i;
        prevb = d;
    }
    return res;
}


void solve() {
    const auto [N] = reads<1>();
    for (const auto v : reads()) {
        cout << dec(v) << " ";
    }
    cout << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
