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


struct checker {
    int n;
    vector<vector<int>> occ; // occurrences
    const string *s, *t;

    pair<bool, vector<int>> check(int L) {
        vector<int> o(n, -1);
        int prev = 0;
        if ((*s)[0] != (*t)[0])
            return {false, {}};
        o[0] = 0;
        prev = 0;

        for (const auto i : views::iota(1, n)) {
            int c = (*t)[i] - 'a';
            int low = max(prev, i - L);
            // find first occurrence >= low
            const auto &v = occ[c];
            auto it = ranges::lower_bound(v, low);
            if (it == v.end() || *it > i)
                return {false, {}};
            o[i] = *it;
            prev = o[i];
        }
        return {true, o};
    }
};


void solve() {
    const auto [N, K] = reads<2>();
    auto s = read();
    const auto target = read();

    if (s[0] != target[0]) {
        cout << -1 << endl;
        return;
    }
    if (s == target) {
        cout << 0 << endl;
        return;
    }

    auto occ = vector(26, vector<int>());
    for (int i = 0; i < N; ++i)
        occ[s[i] - 'a'].push_back(i);

    auto last = vector(26, -1);
    for (int i = 0; i < N; ++i) {
        last[s[i] - 'a'] = i;
        if (last[target[i] - 'a'] == -1) {
            cout << -1 << endl;
            return;
        }
    }

    // bin search?!
    auto C = checker{.n = N, .occ = occ, .s = &s, .t = &target};
    auto lo = 0;
    auto hi = N - 1;
    auto best = N;
    vector<int> best_occ;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        auto [feas, o] = C.check(mid);
        if (feas) {
            best = mid;
            best_occ = move(o);
            hi = mid - 1;
        } else
            lo = mid + 1;
    }
    if (best > K) {
        cout << -1 << '\n';
        return;
    }

    cout << best << '\n';
    auto c = vector<int>(N);
    for (const auto i : views::iota(0, N))
        c[i] = i - best_occ[i];

    auto cur = s;
    for (int r = 1; r <= best; ++r) {
        auto nxt = cur;
        for (const auto i : views::iota(1, N)) {
            if (r <= c[i])
                nxt[i] = cur[i - 1];
        }
        cout << nxt << '\n';
        cur = move(nxt);
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
