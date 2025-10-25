#pragma GCC optimize("Ofast")

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;


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


template<size_t N, typename T = int, bool validate = true>
array<T, N> reads() {
    array<T, N> arr;
    istringstream iss(read());
    auto issv = views::istream<T>(iss) | views::take(N);
    const auto r = ranges::copy(issv, arr.begin());
    if (validate) {
        if (iss.fail() && !iss.eof())
            throw runtime_error("reads() fail: parse error");
        if (r.in.base() != default_sentinel_t{})
            throw runtime_error("reads() fail: excess elements");
        if (r.out != arr.end())
            throw runtime_error("reads() fail: not enough elements");
    }
    return arr;
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
consteval auto c_primes() {
    array<int, C> res{};
    res[0] = 2;
    for (auto i = 3, j = 1; i < N; i += 2) {
        if (Sieve[i / 2])
            res[j++] = i;
    }
    return res;
}


constexpr auto PRIMES = c_primes<200001>();


template<int N>
constexpr array<int, N + 1> first_pfact() {
    array<int, N + 1> res{};
    iota(res.begin(), res.end(), 0);
    for (const auto i : views::iota(2, static_cast<int>(sqrt(N)) + 1)) {
        if (res[i] != i)
            continue;
        for (auto j = i * i; j < N + 1; j += i) {
            if (res[j] == j)
                res[j] = i;
        }
    }
    return res;
}

const auto FPF = first_pfact<200000>();


void solve() {
    const auto [N] = reads<1>();
    auto arr = reads();
    auto cost = reads();

    const auto M = *ranges::max_element(FPF);

    auto min_odd1 = numeric_limits<ll>::max();
    auto min_odd2 = min_odd1;
    auto has = vector(M + 1, false);
    for (const auto [c, v] : views::zip(cost, arr)) {
        if (v % 2) {
            if (c < min_odd1) {
                min_odd2 = min_odd1;
                min_odd1 = c;
            } else if (c < min_odd2) {
                min_odd2 = c;
            }
        }
        if (v == 1)
            continue;
        auto r = v;
        while (r > 1) {
            const auto f = FPF[r];
            if (has[f]) {
                cout << 0 << endl;
                return;
            }
            has[f] = true;
            while (r % f == 0)
                r /= f;
        }
    }

    if (ranges::none_of(has, identity{})) {
        cout << min_odd1 + min_odd2 << endl;
        return;
    }


    auto min_one_cost = numeric_limits<int>::max();
    for (const auto [c, v] : views::zip(cost, arr)) {
        auto r = v + 1;
        while (r > 1) {
            const auto f = FPF[r];
            if (has[f]) {
                min_one_cost = min(min_one_cost, c);
            }
            while (r % f == 0)
                r /= f;
        }
    }


    const auto min_two_cost = min_odd1 + min_odd2;

    cout << min(min_one_cost, min_two_cost) << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
