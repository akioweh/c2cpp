#include <bitset>
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


template<size_t N, typename T = int, bool check_count = true>
array<T, N> reads() {
    array<T, N> arr;
    istringstream iss(read());
    auto r = ranges::copy(views::istream<T>(iss) | views::take(N), arr.begin());
    if (check_count) {
        if (r.out != arr.end())
            throw runtime_error("not enough elements");
        T _;
        if (iss >> _ || !iss.eof())
            throw runtime_error("too many elements");
    }
    return arr;
}


void solve() {
    const auto [N, C] = reads<2>();
    int pattern = 0;
    const auto A = read();
    const auto B = read();
    for (const auto i : views::iota(0, N)) {
        if (A[i] == B[i])
            pattern |= 1 << i;
    }
    auto seen = vector(1 << N, false);
    for (const auto _ : views::iota(0, C)) {
        const auto p = read();
        int idx = 0;
        for (const auto [i, c] : views::enumerate(p)) {
            if (c == '=')
                idx |= 1 << i;
        }
        seen[idx] = true;
    }

    const function<bool(int)> dfs = [&](const int state) {
        for (const auto i : views::iota(0, N)) {
            const auto new_state = state ^ (1 << i);
            if (seen[new_state])
                continue;
            seen[new_state] = true;
            auto res = dfs(new_state);
            seen[new_state] = false;
            if (!res)
                return true;
        }
        return false;
    };

    seen[pattern] = true;
    cout << (dfs(pattern) ? "Alice" : "Bob") << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
