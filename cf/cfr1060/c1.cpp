#pragma GCC optimize("Ofast")

#include <vector>
// #pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>

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

const auto FPF = first_pfact<200001>();


void solve() {

    const auto [N] = reads<1>();
    auto arr = reads();
    auto cost = reads();

    const auto M = *ranges::max_element(FPF);
    auto has = vector(M + 1, false);
    for (const auto v : arr) {
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

    if (has[0]) {
        cout << 1 << endl;
        return;
    }

    for (const auto v : arr) {
        auto r = v + 1;
        while (r > 1) {
            const auto f = FPF[r];
            if (has[f]) {
                cout << 1 << endl;
                return;
            }
            while (r % f == 0)
                r /= f;
        }
    }

    cout << 2 << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
