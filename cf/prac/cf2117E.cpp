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
    const auto as = reads();
    const auto bs = reads();
    vector<bool> seen(N + 1);
    int just_seen_a = 0;
    int just_seen_b = 0;
    for (auto i = N; i--;) {
        if (as[i] == bs[i] || seen[as[i]] || seen[bs[i]] || as[i] == just_seen_a || bs[i] == just_seen_b) {
            cout << i + 1 << endl;
            return;
        }
        seen[just_seen_a] = true;
        seen[just_seen_b] = true;
        just_seen_a = as[i];
        just_seen_b = bs[i];
    }
    cout << 0 << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
