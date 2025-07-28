// #pragma GCC optimize("no-stack-protector,unroll-loops,O3,inline")
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


constexpr int MOD = 998244353;

// precompute ncr mod MOD
constexpr int MAX_N = 501;


consteval int powi(const int x, long long n, const int mod) {
    int res = 1;
    long long val = static_cast<long long>(x) % mod;
    while (n) {
        if (n % 2)
            res = static_cast<long long>(res) * val % mod;
        val = val * val % mod;
        n /= 2;
    }
    return res;
}


consteval auto calc_fact() {
    array<int, MAX_N + 1> fact{};
    fact[0] = 1;
    for (auto i = 1; i <= MAX_N; i++)
        fact[i] = static_cast<long long>(fact[i - 1]) * i % MOD;

    return fact;
}


consteval auto calc_fact_inv(const auto &fact) {
    array<int, MAX_N + 1> fact_inv{};
    fact_inv[MAX_N] = powi(fact[MAX_N], MOD - 2, MOD);
    for (auto i = MAX_N; i--;)
        fact_inv[i] = static_cast<long long>(fact_inv[i + 1]) * (i + 1) % MOD;

    return fact_inv;
}


constexpr auto FACT = calc_fact();
constexpr auto FACT_INV = calc_fact_inv(FACT);


constexpr int ncr(const int n, const int r) {
    return static_cast<long long>(FACT[n]) * FACT_INV[r] % MOD * FACT_INV[n - r] % MOD;
}


void solve() {
    auto [N, K] = reads<2>();
    string arr;
    getline(cin, arr);

    // dp[i][k] = #ways to do k operations with pivots in arr[i:]
    auto prev = vector(K + 1, 0ll);
    prev[0] = 1;

    for (auto i = N; i--;) {
        // calc dp[i] using dp[i + 1]
        auto row = vector(K + 1, 0ll);
        for (auto k = 0; k <= K; k++) {
            // we insert l operations at i between the sequence of operations in arr[i+1:]
            // to get k + l operations in arr[i:]
            for (auto l = 0; k + l <= K; l++) {
                // string of k + l operations, count all l-insert permutations
                // since all l ops on i are the same, == ncr k+l l
                // but every op on i must be at the same index parity... (eliminates half the positions)
                // == ncr (k+l)/2 l, accounting for correct rounding (-1 if arr[i] is 1)
                const auto p = (k + l + 1 - (arr[i] == '1')) / 2;
                if (p < l) continue;
                row[k + l] = (row[k + l] + prev[k] * ncr(p, l)) % MOD;
            }
        }
        prev = move(row);
    }

    cout << prev[K] << endl;
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
