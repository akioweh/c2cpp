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
    const auto arr = reads();
    const auto diff = arr[1] - arr[0];
    vector<int> diffs(N);
    adjacent_difference(arr.begin(), arr.end(), diffs.begin());
    for (const auto d : diffs | views::drop(1)) {
        if (d != diff) {
            cout << "NO" << endl;
            return;
        }
    }
    int m;
    if (diff > 0) {
        m = arr[0] - diff;
    } else {
        m = arr[N - 1] + diff;
    }
    cout << (m < 0 || m % (N + 1) ? "NO" : "YES") << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
