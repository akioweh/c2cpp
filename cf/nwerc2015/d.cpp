// #pragma GCC optimize("Ofast,unroll-loops,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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


template<size_t N, typename T = int>
array<T, N> reads() {
    array<T, N> arr{};
    istringstream iss(read());
    auto r = ranges::copy(views::istream<T>(iss) | views::take(N), arr.begin());
    if (r.out != arr.end()) {
        throw runtime_error("not enough elements");
    }
    return arr;
}


void solve() {
    const auto [N, R, P] = reads<3>();

    vector<ull> cache(N + 1, 0);

    const function<long long(int)> calc = [&](const ull lines) -> ull {
        if (lines == 1)
            return 0;
        if (cache[lines])
            return cache[lines];
        ull res = R + (lines - 1) * P;
        for (ull a = 2; a < min(lines, static_cast<ull>(sqrt(lines)) + 1); ++a) {
            const ull b = ceil(static_cast<long double>(lines) / a);
            const ull c1 = calc(b) + R + (a - 1) * P;
            const ull c2 = calc(a) + R + (b - 1) * P;
            res = min(res, min(c1, c2));
        }
        cache[lines] = res;
        return res;
    };

    cout << calc(N) << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
