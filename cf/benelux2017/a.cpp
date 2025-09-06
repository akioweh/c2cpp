#pragma GCC optimize("Ofast")

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
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
    int M, N;
    double R;
    cin >> M >> N >> R;
    cin.ignore();
    const auto [ax, ay, bx, by] = reads<4>();

    const auto calc = [&](const int ht) {
        auto v = static_cast<double>(abs(ay - ht) + abs(by - ht)) * (R / N);
        auto h = (static_cast<double>(abs(ax - bx)) / M) * (numbers::pi * ht * (R / N));
        return v + h;
    };

    auto rn = views::iota(0, N + 1) | views::transform(calc);
    auto ans = *ranges::min_element(rn);

    cout << setprecision(numeric_limits<double>::max_digits10) << ans << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
