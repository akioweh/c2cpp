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

constexpr long long MOD = 1'000'000'007;


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
    auto r = ranges::copy(
        views::istream<T>(iss) | views::take(N),
        arr.begin()
    );
    if (r.out != arr.end()) { throw runtime_error("not enough elements"); }
    return arr;
}


template<int N>
array<int, N> calc() {
    array<int, N> res{};
    res[0] = 1;
    for (auto i = 1; i < N; ++i) {
        long long tmp = static_cast<long long>(res[i - 1]) * 2;
        if (tmp > MOD)
            tmp -= MOD;
        res[i] = tmp;
    }
    return res;
}


const auto p2s = calc<500002>();


int ll_size(const vector<vector<int>> &adj_list, const int prev, const int cur) {
    auto nx = adj_list[cur];
    erase(nx, prev);
    if (nx.size() > 1)
        return -1;
    if (nx.empty())
        return 1;
    const auto v = ll_size(adj_list, cur, nx[0]);
    if (v == -1)
        return -1;
    return 1 + v;
}


void solve() {
    const auto [N] = reads<1>();
    auto adj_list = vector<vector<int>>(N + 1);
    int u, v;
    for (auto i = 0; i < N - 1; ++i) {
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    cin.ignore();
    // cannot have more than two leaves, otherwise ans = 0
    // i.e. one binary branch at most.
    // okay its easy (trim leaves equally from both branches until linked list, then answer is 2^n)
    int r1, r2;
    int prev = 0;
    int cur = 1;
    while (true) {
        auto &nx = adj_list[cur];
        erase(nx, prev);
        if (nx.size() > 2) {
            cout << 0 << endl;
            return;
        }
        if (nx.size() == 2) {
            r1 = nx[0];
            r2 = nx[1];
            break;
        }
        if (nx.empty()) {
            cout << p2s[N] << endl;
            return;
        }
        prev = cur;
        cur = nx[0];
    }
    const auto l1 = ll_size(adj_list, cur, r1);
    const auto l2 = ll_size(adj_list, cur, r2);
    if (l1 == -1 || l2 == -1) {
        cout << 0 << endl;
        return;
    }
    const int n = N - 2 * min(l1, l2);
    long long ans = p2s[n];
    if (l1 == l2)
        ans *= 2;
    else
        ans += p2s[n - 1];
    if (ans > MOD)
        ans -= MOD;
    cout << ans << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
