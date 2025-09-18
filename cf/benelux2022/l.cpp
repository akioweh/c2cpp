#pragma GCC optimize("Ofast")

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
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


struct a3hsh {
    size_t operator()(const array<int, 3> &arr) const { // values will be small
        return static_cast<ull>(arr[0]) ^ (static_cast<ull>(arr[1]) << 20) ^ (static_cast<ull>(arr[2]) << 40);
    }
};


void solve() {
    const auto [N] = reads<1>();
    auto points = vector<array<int, 3>>(N);
    for (auto &point : points)
        point = reads<3>();

    const auto dist = [&](const auto a, const auto b) {
        const auto &[ax, ay, az] = points[a];
        const auto &[bx, by, bz] = points[b];
        const auto dx = static_cast<ll>(bx - ax);
        const auto dy = static_cast<ll>(by - ay);
        const auto dz = static_cast<ll>(bz - az);
        return sqrt((dx * dx) + (dy * dy) + (dz * dz));
    };

    random_device rd;
    auto gen = mt19937(rd());
    auto udist = uniform_int_distribution<>(0, N - 1);

    auto df = numeric_limits<double>::infinity();
    for (const auto _ : views::iota(0, N)) {
        auto a = udist(gen);
        auto b = udist(gen);
        while (a == b)
            b = udist(gen);
        df = min(df, dist(a, b));
    }
    const auto d = static_cast<int>(ceil(df));

    auto grid = unordered_map<array<int, 3>, vector<int>, a3hsh>();

    for (const auto [i, point] : points | views::enumerate) {
        const auto &[x, y, z] = point;
        grid[{x / d, y / d, z / d}].push_back(static_cast<int>(i));
    }

    auto res = numeric_limits<double>::infinity();
    for (const auto &[coords, bin] : grid) {
        const auto [gx, gy, gz] = coords;
        // intra-box
        for (const auto i : views::iota(0ull, bin.size() - 1)) {
            for (const auto j : views::iota(i + 1, bin.size()))
                res = min(res, dist(bin[i], bin[j]));
        }
        // inter-box
        constexpr array deltas = {-1, 0, 1};
        for (const auto [dx, dy, dz] : views::cartesian_product(deltas, deltas, deltas)) {
            if (dx == 0 && dy == 0 && dz == 0)
                continue;
            const array ngc = {gx + dx, gy + dy, gz + dz};
            if (!grid.contains(ngc))
                continue;
            const auto &other = grid[ngc];
            for (const auto [u, v] : views::cartesian_product(bin, other))
                res = min(res, dist(u, v));
        }
    }

    cout << fixed << setprecision(numeric_limits<double>::max_digits10) << res << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
