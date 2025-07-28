// #pragma GCC optimize("Ofast,unroll-loops,inline")
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


using ll = long long;


void solve() {
    const auto [N] = reads<1>();
    const auto arr = reads<ll>();

    vector<ll> pfm;
    pfm.reserve(N);
    auto cur_max = -1ll;
    for (const auto x : arr) {
        if (x > cur_max) {
            pfm.push_back(x);
            cur_max = x;
        } else {
            pfm.push_back(cur_max);
        }
    }

    vector<ll> sfs;
    sfs.reserve(N);
    auto cur_sum = 0ll;
    for (auto i = N; i--;) {
        cur_sum += arr[i];
        sfs.push_back(cur_sum);
    }

    vector<ll> ans;
    for (auto i = 0; i < N; i++) {
        auto res = sfs[i];
        auto cand = pfm[N - i - 1];
        if (cand > arr[N - i - 1])
            res += cand - arr[N - i - 1];
        ans.push_back(res);
    }

    for (const auto x : ans)
        cout << x << ' ';
    cout << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [T] = reads<1>();
    while (T--) {
        solve();
    }
    return 0;
}
