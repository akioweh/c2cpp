#include <cassert>
#pragma GCC optimize("Ofast")

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
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


void solve() {
    const auto [N, Zs] = reads<2>();
    const auto parent = reads();
    const auto par = [&](const int v) {
        if (v == 0)
            return -1;
        return parent[v - 1] - 1;
    };

    auto children = vector(N, vector<int>());
    for (const auto v : views::iota(1, N)) {
        children[par(v)].push_back(v);
    }

    auto go = true;
    auto levels = vector<vector<int>>();
    levels.push_back(vector({0}));
    while (go && !levels.back().empty()) {
        auto nxt_lvl = vector<int>();
        for (const auto v : levels.back()) {
            if (children[v].empty()) { // leaf node
                go = false;
                break;
            }
            for (const auto w : children[v])
                nxt_lvl.push_back(w);
        }
        levels.push_back(nxt_lvl);
    }
    levels.pop_back();

    const auto min_height = levels.size();

    auto sizes = vector<int>(min_height);
    for (const auto [i, vec] : levels | views::enumerate)
        sizes[i] = vec.size();

    const auto check = [&](const auto ht) {
        const auto s = accumulate(sizes.begin(), sizes.begin() + ht, 0);
        const auto lower = max(0, s - (N - Zs));
        const auto upper = min(s, Zs);
        if (lower > upper)
            return false;

        auto dp = vector(s + 1, false);
        dp[0] = true;
        for (const auto size : sizes) {
            for (auto j = s; j >= size; --j) {
                if (dp[j - size])
                    dp[j] = true;
            }
        }

        for (const auto i : views::iota(lower, upper + 1)) {
            if (dp[i])
                return true;
        }
        return false;
    };

    for (auto ans = min_height; ans > 0; --ans) {
        if (check(ans)) {
            cout << ans << endl;
            return;
        }
    }
    // wtf
    cout << 1 << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
