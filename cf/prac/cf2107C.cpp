// #pragma GCC optimize("no-stack-protector,unroll-loops,O3,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>


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


// max subarray sum
template <ranges::input_range R>
requires same_as<ranges::range_value_t<R>, long long>
long long mss(const R &v) {
    long long max_sum = -1e18;
    long long cur_sum = 0;
    for (const auto &x : v) {
        cur_sum = max(cur_sum + x, x);
        max_sum = max(max_sum, cur_sum);
    }
    return max_sum;
}


// max prefix sum
template <ranges::input_range R>
requires same_as<ranges::range_value_t<R>, long long>
long long mps(const R &v) {
    long long max_sum = -1e18;
    long long acc = 0;
    for (const auto &x : v) {
        acc += x;
        max_sum = max(max_sum, acc);
    }
    return max_sum;
}


void solve() {
    auto [N, K] = reads<2, long long>();
    vector<bool> fixed = reads<char>()
                     | views::transform([](const char c) { return c == '1'; })
                     | ranges::to<vector<bool>>();
    vector<long long> arr = reads<long long>();
    for (auto [i, t] : views::enumerate(fixed))
        if (!t) arr[i] = -1e13;

    const auto sum = mss(arr);
    if ((ranges::all_of(fixed, identity{}) && sum != K) || sum > K) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        if (sum != K) {
            const auto idx = ranges::find(fixed, false) - fixed.begin();
            arr[idx] = 0;  // allow empty
            arr[idx] = K - mps(arr | views::drop(idx)) - mps(arr | views::take(idx + 1) | views::reverse);
        }
        ranges::copy(arr, ostream_iterator<long long>(cout, " "));
        cout << endl;
    }
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
