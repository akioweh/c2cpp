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


int lnds(const auto &rn) {
    if (ranges::empty(rn))
        return 0;
    auto res = vector({rn.front()});
    for (const auto v : rn | views::drop(1)) {
        if (v >= res.back())
            res.push_back(v);
        else
            res[distance(res.begin(), ranges::upper_bound(res, v))] = v;
    }
    return res.size();
}


void solve() {
    const auto [N] = reads<1>();
    const auto [sx, sy, tx, ty] = reads<4>();
    auto points = vector<pair<int, int>>();
    const auto rightward = tx > sx;
    const auto upward = ty > sy;
    auto lx = sx, rx = tx;
    auto ly = sy, ry = ty;
    if (!rightward)
        swap(lx, rx);
    if (!upward)
        swap(ly, ry);

    for (const auto _ : views::iota(0, N)) {
        const auto [x, y] = reads<2>();
        if (x < lx || x > rx || y < ly || y > ry)
            continue;
        points.emplace_back(x, y);
    }

    const auto reversed = rightward != upward;
    if (reversed)
        ranges::sort(points, [](const auto p1, const auto p2) {
            return make_pair(-p1.first, p1.second) < make_pair(-p2.first, p2.second);
        });
    else
        ranges::sort(points);
    const auto ys = points | views::elements<1>;

    cout << lnds(ys) << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
