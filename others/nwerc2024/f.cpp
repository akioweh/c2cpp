#include <functional>
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


void solve() {
    const auto [N, Q] = reads<2>();
    const auto cap = reads();

    auto nxt = vector<int>(N, -1);

    auto stack = vector<pair<int, int>>();
    for (auto i = N; i--;) {
        while (!stack.empty() && stack.back().first <= cap[i])
            stack.pop_back();
        if (!stack.empty())
            nxt[i] = stack.back().second;
        stack.emplace_back(cap[i], i);
    }

    auto res = vector(N, 0);

    const function<int(int)> find_next = [&](auto x) {
        if (res[x] < cap[x])
            return x;
        if (nxt[x] != -1)
            nxt[x] = find_next(nxt[x]);
        return nxt[x];
    };

    for (const auto _ : views::iota(0, Q)) {
        char typ;
        int v, x;
        cin >> typ >> v;
        --v;
        if (typ == '?') {
            cout << res[v] << '\n';
        } else {
            cin >> x;
            while (x) {
                v = find_next(v);
                if (v == -1)
                    break;
                const auto d = min(cap[v] - res[v], x);
                x -= d;
                res[v] += d;
            }
        }
        cin.ignore();
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
