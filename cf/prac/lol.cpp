// #pragma GCC optimize("Ofast,unroll-loops,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;


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
    const auto [a, b, c, d] = reads<4, ll>();
    const ll MIN = min(min(a, b), c);
    ll best_ans = 0;
    for (ll target_min = MIN; target_min < MIN + 100000000; ++target_min) {
        ll a2 = a, b2 = b, c2 = c;
        ll ans = 0;
        ll req = max(0ll, target_min - a2) + max(0ll, target_min - b2) + max(0ll, target_min - c2);
        if (req > d)
            break;

        a2 = max(a2, target_min);
        b2 = max(b2, target_min);
        c2 = max(c2, target_min);

        const ll rem = d - req;

        if (a2 >= b2 && a2 >= c2) {
            a2 += rem;
        } else if (b2 >= a2 && b2 >= c2) {
            b2 += rem;
        } else {
            c2 += rem;
        }
        ans = a2 * a2 + b2 * b2 + c2 * c2 + 7 * target_min;
        best_ans = max(best_ans, ans);
    }
    cout << best_ans << endl;
}
