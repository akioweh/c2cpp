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


void solve() {
    const auto [W, H, A, B] = reads<4>();
    const auto [X1, Y1, X2, Y2] = reads<4>();
    if (X1 == X2) {
        cout << ((Y2 - Y1) % B ? "NO" : "YES") << endl;
        return;
    }
    if (Y1 == Y2) {
        cout << ((X2 - X1) % A ? "NO" : "YES") << endl;
        return;
    }
    cout << ((X2 - X1) % A && (Y2 - Y1) % B ? "NO" : "YES") << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
