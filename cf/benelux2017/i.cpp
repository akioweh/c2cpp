#pragma GCC optimize("Ofast")

#include <vector>
#pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
#include <functional>
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
    const auto [H, W] = reads<2>();

    constexpr int senti = 756424794;
    auto memom = vector(H + 1, vector<int>(W + 1, senti));
    auto memof = vector(H + 1, vector<int>(W + 1, senti));

    const function<int(int, int, bool)> get = [&](const int h, const int w, const bool sex) {
        return sex ? memom[h][w] : memof[h][w];
    };

    const function<void(int, int, bool, int)> set = [&](const int h, const int w, const bool sex, const int val) {
        // cout << "set " << val << " for " << h << ' ' << w << ' ' << sex << endl;
        if (sex)
            memom[h][w] = val;
        else
            memof[h][w] = val;
    };

    const function<int(int, int, bool)> brrr = [&](const int h, const int w, const bool sex) {
        if (h == 0 || w == 0)
            return 0;
        const auto m = get(h, w, sex);
        if (m != senti)
            return m;

        int res;
        if (sex) {
            auto rn = views::iota(1, w + 1) | views::transform([&](const int b) {
                          auto nxt = brrr(h, w - b, false);
                          if (b % 2 && h % 2)
                              nxt += ((W - w) % 2 /*  white */) ? -1 : 1;
                          return nxt;
                      });
            res = *ranges::max_element(rn);
        } else {
            auto rn = views::iota(1, h + 1) | views::transform([&](const int b) {
                          auto nxt = brrr(h - b, w, true);
                          if (b % 2 && w % 2)
                              nxt += ((W % 2 != h % 2) /* white */) ? 1 : -1;
                          return nxt;
                      });
            res = *ranges::min_element(rn);
        }
        set(h, w, sex, res);
        return res;
    };


    cout << brrr(H, W, true) << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
