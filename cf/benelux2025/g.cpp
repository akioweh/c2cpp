#include <array>
#include <random>
#pragma GCC optimize("Ofast")

#include <vector>
#pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
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


struct TN {
    bool end{};
    array<TN *, 26> nxt{};
};


void solve() {
    const auto s = read();
    const auto [N] = reads<1>();
    const auto M = static_cast<int>(s.length());

    auto root = TN();

    const auto insert = [&](const string &s) {
        auto *cur = &root;
        for (const auto c : s) {
            const auto v = c - 'a';
            if (cur->nxt[v] == nullptr)
                cur->nxt[v] = new TN();
            cur = cur->nxt[v];
        }
        cur->end = true;
    };


    const auto match = [&](const int start) -> bool {
        auto *cur = &root;
        for (const auto i : views::iota(start, M)) {
            const auto v = s[i] - 'a';
            if (cur->nxt[v] == nullptr)
                return false;
            cur = cur->nxt[v];
            if (cur->end)
                return true;
        }
        return true; // whatever
    };


    const auto try_match = [&](const int start) -> bool {
        for (const auto i : views::iota(start, min(start + 10, M - 5))) {
            if (match(i))
                return true;
        }
        return false;
    };


    for (const auto _ : views::iota(0, N))
        insert(read());


    auto rd = random_device();
    auto rng = mt19937(rd());
    auto udist = uniform_int_distribution<>(0, M - 11);

    for (const auto _ : views::iota(0, 8000)) {
        if (!try_match(udist(rng))) {
            cout << "no" << endl;
            return;
        }
    }
    cout << "yes" << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
