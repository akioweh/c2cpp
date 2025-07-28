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
    const auto [N, Q] = reads<2>();
    string s = read();  // s contains only a, b, or c
    // once again, graph ahh problem (i might be stretching it this time)
    int b_a = 0, b_c = 0, c_a = 0, c_b = 0, b_c_a = 0, c_b_a = 0;
    for (auto q = 0; q < Q; ++q) {
        const auto [u, v] = reads<2, char>();
        if (u == v || u == 'a')
            continue;
        if (u == 'b') {
            if (v == 'a') {
                if (c_b) {
                    ++c_b_a;
                    --c_b;
                } else {
                    ++b_a;
                }
            } else {  // v == 'c'
                ++b_c;
            }
        } else {  // u == 'c'
            if (v == 'a') {
                if (b_c) {
                    ++b_c_a;
                    --b_c;
                } else {
                    ++c_a;
                }
            } else {  // v == 'b'
                ++c_b;
            }
        }
    }

    for (auto &c : s) {
        if (c == 'a')
            continue;
        if (c == 'b') {
            if (b_a) {
                --b_a;
                c = 'a';
            } else if (c_b_a) {
                --c_b_a;
                ++c_b;
                c = 'a';
            } else if (b_c_a) {
                --b_c_a;
                c = 'a';
            }
        } else {  // c == 'c'
            if (c_a) {
                --c_a;
                c = 'a';
            } else if (b_c_a) {
                --b_c_a;
                ++b_c;
                c = 'a';
            } else if (c_b_a) {
                --c_b_a;
                c = 'a';
            } else if (c_b) {
                --c_b;
                c = 'b';
            }
        }
    }
    cout << s << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
