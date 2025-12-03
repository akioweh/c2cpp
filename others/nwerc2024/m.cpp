#pragma GCC optimize("Ofast")

#include <vector>
#pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
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


struct Vec2 {
    double x;
    double y;

    constexpr Vec2() noexcept : x(0), y(0) {}
    template<typename T>
    constexpr Vec2(pair<T, T> pi) noexcept : x(pi.first), y(pi.second) {}
    template<typename T>
    constexpr Vec2(array<T, 2> ai) noexcept : x(ai[0]), y(ai[1]) {}
    template<typename T>
    constexpr Vec2(T x, T y) noexcept : x(x), y(y) {}
    constexpr Vec2 operator+(const Vec2 &other) const noexcept { return {x + other.x, y + other.y}; }
    constexpr Vec2 operator-() const noexcept { return {-x, -y}; }
    constexpr Vec2 operator-(const Vec2 &other) const noexcept { return *this + (-other); }
    template<typename T>
    constexpr Vec2 operator*(const T a) const noexcept {
        return {x * a, y * a};
    }
    constexpr friend double operator^(const Vec2 &a, const Vec2 &b) { return a.x * b.y - a.y * b.x; }
    friend constexpr ostream &operator<<(ostream &os, const Vec2 &v) { return os << '(' << v.x << ',' << v.y << ')'; }
};


void solve() {
    const auto [N] = reads<1>();
    auto pts = vector<Vec2>();
    pts.reserve(N);
    for (auto _ = 0; _ < N; ++_)
        pts.emplace_back(reads<2>());

    // for tri in {all triangles}
    //     res += area(tri)
    //
    // res /= tot_area * size({all triangles})

    auto tot_area = (pts.back() ^ pts.front());
    for (const auto [a, b] : views::pairwise(pts))
        tot_area += a ^ b;
    tot_area /= 2;

    auto pfs = vector<Vec2>();
    pfs.reserve(N);
    partial_sum(pts.begin(), pts.end(), back_inserter(pfs));

    auto res = 0.;
    for (auto i = 1; i < N - 1; ++i)
        res += (pts[i] * i - pfs[i - 1]) ^ (pfs.back() - pfs[i] - pts[i] * (N - 1 - i));
    res /= 2;

    res /= tot_area;
    cout << scientific << setprecision(numeric_limits<double>::max_digits10) << res << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
