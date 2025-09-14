#pragma GCC optimize("Ofast")

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
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
    const auto [N, K, target] = reads<3, ll>();
    auto vs = reads();
    ranges::sort(vs);

    const auto tot = accumulate(vs.begin(), vs.end(), 0ll);
    ll t;

    // k = 0
    auto means = vector<double>({static_cast<double>(tot) / N});

    // k = 1
    t = tot - target * (N - 1);
    const auto b = ranges::lower_bound(vs, t);
    const auto a = b - 1;
    vector<int>::iterator s;
    if (b == vs.begin())
        s = b;
    else if (b == vs.end())
        s = a;
    else
        s = (*b - t) < (t - *a) ? b : a;
    means.push_back(static_cast<double>(tot - *s) / (N - 1));

    const auto two_sum = [&](const ll li, const ll ri, const ll t) {
        auto best_diff = numeric_limits<ll>::max();
        auto best_sum = -1ll;
        auto l = vs.cbegin() + li;
        auto r = vs.cbegin() + ri - 1;
        while (l != r) {
            const auto cur = static_cast<ll>(*l) + *r;
            if (abs(cur - t) < best_diff) {
                best_diff = abs(cur - t);
                best_sum = cur;
            }
            if (cur > t)
                --r;
            else
                ++l;
        }
        return best_sum;
    };

    if (K >= 2) {
        t = tot - target * (N - 2);
        means.push_back(static_cast<double>(tot - two_sum(0, N, t)) / (N - 2));
    }

    if (K >= 3) {
        t = tot - target * (N - 3);
        auto best_diff = numeric_limits<ll>::max();
        auto best_sum = -1ll;
        for (const auto i : views::iota(0, N - 2)) {
            const auto a = vs[i];
            const auto cur = a + two_sum(i + 1, N, t - a);
            if (abs(cur - t) < best_diff) {
                best_diff = abs(cur - t);
                best_sum = cur;
            }
        }
        means.push_back(static_cast<double>(tot - best_sum) / (N - 3));
    }

    if (K == 4) { // would this work?
        t = tot - target * (N - 4);
        auto ps = map<ll, vector<pair<int, int>>>();
        for (const auto i : views::iota(0, N - 1)) {
            for (const auto j : views::iota(i + 1, N))
                ps[vs[i] + vs[j]].emplace_back(i, j);
        }
        auto best_diff = numeric_limits<ll>::max();
        auto best_sum = -1ll;
        auto l = ps.begin();
        auto r = ps.rbegin();
        while (l != r.base()) {
            const auto cur = l->first + r->first;
            auto good = false;
            for (const auto &[a, b] : l->second) {
                for (const auto &[c, d] : r->second) {
                    if (a == c || a == d || b == c || b == d)
                        continue;
                    good = true;
                    break;
                }
                if (good)
                    break;
            }
            if (good) {
                const auto diff = abs(cur - t);
                if (diff < best_diff) {
                    best_diff = diff;
                    best_sum = cur;
                }
            }
            if (cur > t)
                ++r;
            else
                ++l;
        }
        means.push_back(static_cast<double>(tot - best_sum) / (N - 4));
    }

    auto rn = means | views::transform([&](const auto v) { return abs(v - target); });
    cout << *ranges::min_element(rn) << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
