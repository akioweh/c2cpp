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


void solve() {
    auto [N, K] = reads<2>();
    const vector s = reads<char>()
                     | views::transform([](const char c) { return c - 'a'; })
                     | ranges::to<vector<unsigned char>>();
    vector<vector<int>> delt(N);  // delt[i][c] <- idx of first c in s[i:]
    vector<int> min_jump(N + 2);  // min number of jumps to leave s[i+1:]
    delt[N - 1].assign(K, N);
    delt[N - 1][s[N - 1]] = N - 1;
    min_jump[N + 1] = min_jump[N] = 0;
    min_jump[N - 1] = 1;
    for (auto i = N - 1; i--;) {
        delt[i] = delt[i + 1];
        delt[i][s[i]] = i;
        min_jump[i] = min_jump[*ranges::max_element(delt[i + 1])] + 1;
    }

    auto [Q] = reads<1>();
    while (Q--) {
        const auto t = reads<char>()
                       | views::transform([](const char c) { return c - 'a'; });
        int idx = -1;  // last match
        for (const auto c : t) {
            if (++idx >= N)
                break;
            idx = delt[idx][c];
        }
        cout << min_jump[idx] << endl;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
