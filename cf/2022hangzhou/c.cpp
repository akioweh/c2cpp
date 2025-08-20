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
    const auto [N, K] = reads<2>();
    auto W = vector<vector<int>>(N);
    for (auto &r : W)
        r = reads();

    constexpr ll NINF = numeric_limits<ll>::min();
    // dp[i][w][p] = max score using W[:i] with tot weight == w and p (0/1) partial upgrades
    auto prev_row = vector(K + 1, array<ll, 2>{NINF, NINF});
    prev_row[0][0] = 0;
    vector<array<ll, 2>> row;
    for (const auto &item : W) {
        row = prev_row;
        for (const auto w : views::iota(1, K + 1)) {
            const auto iw = item.front();
            const auto score = item.back();
            if (iw <= w) { // full
                row[w][0] = max(row[w][0], prev_row[w - iw][0] + score);
                row[w][1] = max(row[w][1], prev_row[w - iw][1] + score);
            }
            // partial
            for (const auto [iw, score] : views::enumerate(item) | views::drop(1)) {
                if (iw > w)
                    break;
                row[w][1] = max(row[w][1], prev_row[w - iw][0] + score);
            }
        }
        swap(prev_row, row);
    }

    auto ans = prev_row[K][1];
    for (const auto &p : prev_row)
        ans = max(ans, p[0]);
    cout << ans << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
