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


constexpr unsigned long long MOD = 998'244'353;


consteval unsigned long long powi(const unsigned long long x, unsigned long long n, const unsigned long long mod) {
    unsigned long long res = 1;
    unsigned long long val = x % mod;
    while (n) {
        if (n % 2)
            res = res * val % mod;
        val = val * val % mod;
        n /= 2;
    }
    return res;
}


void solve() {
    const auto [N, M, A, B] = reads<4>();
    unsigned long long ans = 0;
    ans += (A + 1) * (B + 1) % MOD;  // {u} x {v}  (res -> 1 value)
    // ans += (A + 1) * (B+1 choose 2 = (B + 1)*B/2) * (2**M) + the other side  // {u} x {v, w}  (res -> 1 or 2 values)
    auto tmp = (A + 1) % MOD;
    tmp = tmp * (B + 1) * B / 2 % MOD;
    tmp = tmp * powi(2, M, MOD) % MOD;
    ans = (ans + tmp) % MOD;
    tmp = (B + 1) % MOD;
    tmp = tmp * (A + 1) * A / 2 % MOD;
    tmp = tmp * powi(2, N, MOD) % MOD;
    ans = (ans + tmp) % MOD;

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [T] = reads<1, int>();
    while (T--) {
        solve();
    }
    return 0;
}
