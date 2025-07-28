// #pragma GCC optimize("Ofast,unroll-loops,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


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


template<size_t N, typename T = int>
array<T, N> reads() {
    array<T, N> arr{};
    istringstream iss(read());
    auto r = ranges::copy(views::istream<T>(iss) | views::take(N), arr.begin());
    if (r.out != arr.end()) {
        throw runtime_error("not enough elements");
    }
    return arr;
}


void solve() {
    const auto [N, M] = reads<2>();
    vector<pair<int, int>> times(N);
    for (auto &[s, e] : times) {
        const auto [s_, d] = reads<2>();
        s = s_;
        e = s_ + d;
    }
    ranges::sort(times);
    priority_queue<int, vector<int>, greater<int>> in_use;
    int ans = 0;
    for (const auto &[s, e] : times) {
        while (!in_use.empty() && in_use.top() + M < s)
            in_use.pop();

        if (!in_use.empty() && in_use.top() <= s) {
            ans += 1;
            in_use.pop();
        }

        in_use.push(e);
    }

    cout << ans << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
