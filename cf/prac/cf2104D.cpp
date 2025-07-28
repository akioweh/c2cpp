#pragma GCC optimize("no-stack-protector,unroll-loops,O3,inline")

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

#pragma GCC target("avx2,fma,bmi2,popcnt,lzcnt")


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


constexpr unsigned long long MAX_P = 4e5;


vector<unsigned long long> primes(const unsigned long long n) {
    const unsigned long long sieve_max = n * bit_width(n);
    vector is_prime(sieve_max, true);
    vector<unsigned long long> res;
    res.reserve(n);
    for (auto i = 2ull; i < sieve_max; i++) {
        if (!is_prime[i]) continue;
        res.push_back(i);
        if (res.size() == n) break;
        for (auto j = i * i; j < sieve_max; j += i)
            is_prime[j] = false;
    }
    assert(res.size() == n);
    return res;
}


const auto PRIMES = primes(MAX_P);


void solve() {
    auto [N] = reads<1>();
    auto nums = reads();
    unsigned long long n_tot = accumulate(nums.begin(), nums.end(), 0ull);
    unsigned long long p_tot = accumulate(PRIMES.begin(), PRIMES.begin() + N, 0ull);
    ranges::make_heap(nums, greater{});
    for (auto n = 0; n < N; n++) {
        if (n_tot >= p_tot) {
            cout << n << endl;
            return;
        }
        const unsigned long long next_n = nums.front();
        pop_heap(nums.begin(), nums.end() - n, greater{});
        const auto next_p = PRIMES[N - n - 1];
        if (next_n > next_p)
            break;
        n_tot -= next_n;
        p_tot -= next_p;
    }
    cout << N << endl;
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
