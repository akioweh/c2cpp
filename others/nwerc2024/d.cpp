#include <numeric>
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
    auto seats = reads();

    ranges::sort(seats, greater{});
    const auto M = accumulate(seats.begin(), seats.end(), 0);
    const auto thresh = M / 2 + 1;

    auto res = 0ll;
    auto dp = vector(M + 1, 0ll); // dp [m] = how many subsets sum to m?
    dp[0] = 1;
    for (const auto i : views::iota(0, N)) {
        const auto s = seats[i];
        for (const auto m : views::iota(max(0, thresh - s), thresh))
            res += dp[m];
        for (auto m = M + 1; m-- > s;)
            dp[m] += dp[m - s];
    }

    cout << res << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
