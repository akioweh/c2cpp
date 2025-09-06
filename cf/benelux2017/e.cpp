#pragma GCC optimize("Ofast")

#include <functional>
#include <vector>
#pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
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


int kuhn(const vector<vector<int>> &graph, const int M) {
    const auto N = static_cast<int>(graph.size());
    auto rmatch = vector(M, -1);
    auto seen = vector<bool>(N);

    const function<bool(int)> match = [&](const int u) {
        if (seen[u])
            return false;
        seen[u] = true;
        for (const auto v : graph[u]) {
            if (rmatch[v] == -1 || match(rmatch[v])) {
                rmatch[v] = u;
                return true;
            }
        }
        return false;
    };

    auto res = 0;
    for (const auto v : views::iota(0, N)) {
        seen.assign(N, false);
        res += match(v);
    }

    return res;
}


void solve() {
    const auto [N, B, R] = reads<3>();
    auto blus = vector<pair<int, int>>(B);
    auto reds = vector<pair<int, int>>(R);
    for (auto &p : blus)
        p = reads<2>();
    for (auto &p : reds)
        p = reads<2>();

    const auto dist = [&](const auto red, const auto blu) {
        const auto &[rx, ry] = reds[red];
        const auto &[bx, by] = blus[blu];
        return hypot(rx - bx, ry - by);
    };

    const auto check = [&](const double min_dist) {
        auto lgraph = vector(R, vector<int>());
        for (auto [red, adj] : views::enumerate(lgraph)) {
            for (const auto blu : views::iota(0, B)) {
                if (dist(red, blu) < min_dist)
                    adj.push_back(blu);
            }
        }

        const auto vertex_cover_size = kuhn(lgraph, B);
        const auto maximum_independent_set_size = (R + B) - vertex_cover_size;
        return maximum_independent_set_size >= N;
    };

    auto l = 0.;
    auto r = 1e5;
    const auto tol = 5e-7;
    while (r - l > tol) {
        const auto m = (l + r) / 2;
        if (check(m))
            l = m;
        else
            r = m;
    }
    cout << setprecision(numeric_limits<double>::max_digits10) << l << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
