// pure cpu cycles

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ull = unsigned long long;
using ll = long long;


int powi(int b, ull e, const int m) {
    assert(m > 0);
    int res = 1;
    b = (b % m + m) % m; // ensures b is positive
    while (e) {
        if (e % 2)
            res = static_cast<ll>(res) * b % m;
        b = static_cast<ll>(b) * b % m;
        e /= 2;
    }
    return res;
}


ll powll(ll b, ull e, const ll m) {
    assert(m > 0);
    ll res = 1;
    b = (b % m + m) % m; // ensures b is positive
    while (e) {
        if (e % 2)
            res = res * b % m;
        b = b * b % m;
        e /= 2;
    }
    return res > 0 ? res : res + m;
}


// as + bt = gcd(a, b)
int gcd(const int a, const int b, int &s, int &t) {
    s = 1, t = 0;
    int s1 = 0, t1 = 1, r = a, r1 = b;
    while (r1) {
        const auto q = r / r1;
        tie(r, r1) = make_pair(r1, r - q * r1);
        tie(s, s1) = make_pair(s1, s - q * s1);
        tie(t, t1) = make_pair(t1, t - q * t1);
    }
    return r;
}


// returns 0 if no inverse exists
int mod_inverse(const int a, const int m) {
    int x, y;
    if (gcd(a, m, x, y) != 1)
        return 0;
    return (x % m + m) % m; // ensures positive result
}


vector<int> primes(const int sieve_max) {
    vector res = {2}; // start with 2
    vector is_prime(sieve_max / 2, true); // odd numbers only
    for (auto i = 3; i < sieve_max; i += 2) {
        if (!is_prime[i / 2])
            continue;
        res.push_back(i);
        for (auto j = i * i; j < sieve_max; j += i * 2)
            is_prime[j / 2] = false;
    }
    return res;
}


int phi(int n) {
    int result = n;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}


constexpr auto prime_fact(int n, const vector<int> &primes) {
    vector<int> factors;
    vector<int> exponents;
    // 2 shortcut
    if (const auto m = __builtin_ctz(n & -n)) {
        factors.push_back(2);
        exponents.push_back(m);
        n >>= m;
    }
    for (const auto p : primes) {
        if (p * p > n)
            break;
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
    return make_pair(factors, exponents);
}


template<int N>
constexpr array<bool, N / 2> s_primes() {
    array<bool, N / 2> is_prime{}; // odd numbers only
    ranges::fill(is_prime, true);
    for (auto i = 3ll; i < N; i += 2) {
        if (!is_prime[i / 2])
            continue;
        for (auto j = i * i; j < N; j += i * 2)
            is_prime[j / 2] = false;
    }
    return is_prime;
}


template<int N, array<bool, N / 2> Sieve = s_primes<N>(), int C = ranges::count(Sieve, true)>
constexpr auto c_primes() {
    array<int, C> res{};
    res[0] = 2;
    for (auto i = 3, j = 1; i < N; i += 2) {
        if (Sieve[i / 2])
            res[j++] = i;
    }
    return res;
}


template<int N, size_t C>
constexpr array<int, N> s_phi(array<int, C> _primes) { // an array of primes is required
    array<int, N> res{};
    iota(res.begin(), res.end(), 0);
    for (const auto p : _primes) {
        for (auto i = 1ll; i * p < N; ++i)
            res[i * p] -= res[i * p] / p;
    }
    return res;
}


const auto primes_ = c_primes<100001>();
const auto phi_ = s_phi<100001>(primes_);


int main() {
    for (auto v : phi_) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
