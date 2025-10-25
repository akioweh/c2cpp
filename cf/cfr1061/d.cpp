#include <limits>
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
    const auto [N] = reads<1>();

    auto positions = vector<int>(N - 1);
    for (int i = 0; i < N - 1; ++i) {
        positions[i] = i + 1;
    }
    auto possible = vector<int>(N);
    for (int i = 0; i < N; ++i) {
        possible[i] = i + 1;
    }

    while (possible.size() > 1) {
        auto best_k = -1;
        auto best_max = numeric_limits<int>::max();
        auto curr_size = static_cast<int>(possible.size());

        for (int k = 0; k < 15; ++k) {
            auto set_cnt = 0;
            for (const auto v : possible) {
                if (v & (1 << k))
                    ++set_cnt;
            }
            auto split1 = set_cnt;
            auto split2 = curr_size - set_cnt;
            auto max_split = max(split1, split2);
            if (max_split < best_max) {
                best_max = max_split;
                best_k = k;
            }
        }

        auto x = 1ll << best_k;
        auto expected_set = 0;
        for (const auto v : possible) {
            if (v & (1 << best_k))
                ++expected_set;
        }

        auto count_set = 0;
        vector<int> pos_set, pos_unset;
        for (const auto i : positions) {
            cout << "? " << i << " " << x << endl;
            const auto [res] = reads<1>();
            if (res == 1) {
                ++count_set;
                pos_set.push_back(i);
            } else {
                pos_unset.push_back(i);
            }
        }

        auto missing_has_set = (count_set == expected_set - 1);

        auto new_possible = vector<int>();
        for (const auto v : possible) {
            auto v_has_set = (v & (1 << best_k)) != 0;
            if (v_has_set == missing_has_set)
                new_possible.push_back(v);
        }
        possible = new_possible;

        if (missing_has_set)
            positions = pos_set;
        else
            positions = pos_unset;
    }

    cout << "! " << possible[0] << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
