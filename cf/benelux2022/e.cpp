#include <iomanip>
#include <numeric>
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


void solve() {
    const auto [N, X] = reads<2>();
    const auto vs = reads();

    if (accumulate(vs.begin(), vs.end(), 0) == 0) {
        for (const auto _ : views::iota(0, N))
            cout << 0 << ' ';
        cout << endl;
        return;
    }

    const auto calc = [&](const double fact) {
        auto rn = vs | views::transform([&](const auto v) { return v * fact; }) |
                  views::transform([&](const auto v) { return v * v; });
        return accumulate(rn.begin(), rn.end(), 0.) / N;
    };

    auto l = 0.;
    auto r = 1e9;
    for (const auto _ : views::iota(0, 500)) {
        const auto m = (l + r) / 2;
        if (calc(m) > X)
            r = m;
        else
            l = m;
    }

    for (const auto v : vs) {
        cout << fixed << setprecision(15) << l * v << ' ';
    }
    cout << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
