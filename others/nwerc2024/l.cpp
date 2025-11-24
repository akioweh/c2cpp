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
    const auto [N, M, X, Y] = reads<4>();
    auto shelf = reads();
    auto book = reads();
    ranges::sort(shelf);
    ranges::sort(book);

    const auto check = [&](const int k) {
        // smallest k shelves have reduced capacity
        auto it = book.crbegin();
        for (auto i = N; i--;) {
            for (auto _ = 0; _ < (i < k ? Y : X); ++_) {
                if (*it > shelf[i])
                    return false;
                ++it;
                if (it == book.crend())
                    return true;
            }
        }
        return false;
    };

    const auto rn = views::iota(0, N + 1);
    const auto res = *ranges::partition_point(rn, check) - 1;
    if (res < 0)
        cout << "impossible\n";
    else
        cout << res << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
