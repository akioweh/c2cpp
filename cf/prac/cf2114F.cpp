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


consteval auto primes() {
    constexpr int sieve_max = 1010;
    array<int, 200> res{};
    array<bool, sieve_max / 2> is_prime{};  // odd numbers only
    is_prime.fill(true);
    int idx = 0;  // ignore 2
    for (int i = 3; i < sieve_max; i += 2) {
        if (!is_prime[i / 2]) continue;
        res[idx++] = i;
        for (int j = i * i; j < sieve_max; j += i * 2) {
            is_prime[j / 2] = false;
        }
    }
    return res;
}


constexpr auto PRIMES = primes();


constexpr pair<vector<int>, vector<int>> prime_fact(int n) {
    vector<int> factors;
    vector<int> exponents;
    // 2 shortcut
    if (const auto m = __builtin_ctz(n & -n)) {
        factors.push_back(2);
        exponents.push_back(m);
        n >>= m;
    }
    for (const auto p : PRIMES) {
        if (p * p > n) break;
        if (n % p == 0) {
            factors.push_back(p);
            int exp = 0;
            while (n % p == 0) {
                n /= p;
                exp++;
            }
            exponents.push_back(exp);
        }
    }
    if (n > 1) {
        factors.push_back(n);
        exponents.push_back(1);
    }
    return {factors, exponents};
}


int calc(const int x, const int lim) {
    const auto [prm, cnt] = prime_fact(x);
    const auto t = prm.size();
    if (!t)
        return 0;
    if (prm.back() > lim)
        return -1;

    vector<int> rdx;
    rdx.push_back(1);
    for (auto i = 0; i < t; i++)
        rdx.push_back(rdx.back() * (cnt[i] + 1));
    const int n = rdx.back();
    const int tc = accumulate(cnt.begin(), cnt.end(), 0);

    auto dp = vector(n + 1, make_pair(tc + 1, 1));
    dp[0] = {1, 1};
    for (auto state = 0; state < n; state++) {
        auto [n_bins, fill] = dp[state];
        auto v = state;
        auto s = vector<int>(t);
        for (auto i = t; i--;) {
            s[i] = v / rdx[i];
            v %= rdx[i];
        }
        for (auto k = 0; k < t; k++) {
            if (s[k] == cnt[k])
                continue;
            pair<int, int> cand;
            if (fill * prm[k] <= lim)
                cand = {n_bins, fill * prm[k]};
            else
                cand = {n_bins + 1, prm[k]};
            dp[state + rdx[k]] = min(dp[state + rdx[k]], cand);
        }
    }
    return dp[n - 1].first;
}


void solve() {
    const auto [X, Y, lim] = reads<3>();
    const auto g = gcd(X, Y);
    const auto a = calc(X / g, lim);
    const auto b = calc(Y / g, lim);
    if (a == -1 || b == -1) {
        cout << -1 << endl;
        return;
    }
    cout << a + b << endl;
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
