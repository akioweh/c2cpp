#pragma GCC optimize("Ofast")

#include <vector>
#pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
#include <cstdio>
#include <iostream>
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


int ask(const int l, const int r) {
    cout << "? " << l << ' ' << r << endl;
    fflush(stdout);
    return reads<1>()[0];
}


void solve() {
    const auto [N, Q] = reads<2>();
    auto queries = vector<pair<int, int>>();
    queries.reserve(Q);
    for (const auto _ : views::iota(0, Q)) {
        const auto [l, r] = reads<2>();
        queries.emplace_back(l, r);
    }

    const auto check = [&](const int mid) -> bool {
        if (mid == 0)
            return true;
        const auto v = mid - 1;
        // minp: largest l ask(l, N) > v
        int lo = 1, hi = N;
        auto minp = 0;
        while (lo <= hi) {
            const auto md = (lo + hi) / 2;
            const auto mex = ask(md, N);
            if (mex > v) {
                minp = md;
                lo = md + 1;
            } else {
                hi = md - 1;
            }
        }
        if (minp == 0)
            return false;
        // maxp: smallest r  ask(1, r) > v
        lo = 1, hi = N;
        auto maxp = 0;
        while (lo <= hi) {
            const auto md = (lo + hi) / 2;
            const auto mex = ask(1, md);
            if (mex > v) {
                maxp = md;
                hi = md - 1;
            } else {
                lo = md + 1;
            }
        }
        if (maxp == 0)
            return false;
        if (minp > maxp)
            return false;
        auto cov = false;
        for (const auto [l, r] : queries) {
            if (l <= minp && r >= maxp) {
                cov = true;
                break;
            }
        }
        return cov;
    };

    auto left = 0;
    auto right = N + 1;
    while (left < right) {
        const auto md = (left + right + 1) / 2;
        if (check(md)) {
            left = md;
        } else {
            right = md - 1;
        }
    }
    cout << "! " << left << endl;
    fflush(stdout);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
