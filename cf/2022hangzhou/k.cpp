#pragma GCC optimize("Ofast")

#include <algorithm>
#include <iostream>
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
    const auto [N, Q] = reads<2>();
    auto idx = 0;
    auto nxt = vector<array<int, 26>>();
    auto size = vector<int>();
    nxt.push_back(array<int, 26>{});
    size.push_back(0);

    auto cnt = array<array<ll, 26>, 26>{};
    auto always = 0ll;

    const auto insert = [&](const string &&str) {
        auto cur_i = 0;
        for (const auto c : str) {
            const auto i = c - 'a';
            for (const auto [j, ni] : views::enumerate(nxt[cur_i])) {
                if (i == j || !ni)
                    continue;
                cnt[i][j] += size[ni];
            }
            if (!nxt[cur_i][i]) {
                nxt.push_back(array<int, 26>{});
                size.push_back(0);
                nxt[cur_i][i] = ++idx;
            }
            cur_i = nxt[cur_i][i];
            ++size[cur_i];
        }
        if (!cur_i)
            return;
        for (const auto ni : nxt[cur_i] | views::filter(identity{}))
            always += size[ni];
    };

    for (const auto _ : views::iota(0, N))
        insert(read());

    for (const auto _ : views::iota(0, Q)) {
        const auto s = read();
        auto rank = array<int, 26>{};
        for (const auto [i, c] : views::enumerate(s))
            rank[c - 'a'] = static_cast<int>(i);

        auto ans = always;
        for (const auto [u, v] : views::cartesian_product(views::iota(0, 26), views::iota(0, 26))) {
            if (u == v)
                continue;
            if (rank[u] < rank[v])
                ans += cnt[u][v];
        }
        cout << ans << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
