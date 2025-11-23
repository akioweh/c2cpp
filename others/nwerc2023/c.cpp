#pragma GCC optimize("Ofast")

#include <vector>
#pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <utility>

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


int gcd(const int a, const int b, int &s, int &t) {
    s = 1, t = 0;
    int s1 = 0, t1 = 1, r = a, r1 = b;
    while (r1) {
        const auto q = r / r1;
        tie(r, r1) = make_pair(r1, r - q * r1);
        tie(s, s1) = make_pair(s1, s - q * s1);
        tie(t, t1) = make_pair(t1, t - q * t1);
    }
    return r;
}


int mod_inverse(const int a, const int m) {
    int x, y;
    if (gcd(a, m, x, y) != 1)
        return 0;
    return (x % m + m) % m;
}


void solve() {
    const auto [N, Q] = reads<2>();

    auto players = views::iota(0, N) | ranges::to<vector>();
    players[0] = N;
    auto r = N; // # of residue classes left
    auto m = 1ll;
    auto b = 0ll;
    auto mul = 1ll;
    auto add = 0ll;

    // players array is of "compressed" indices
    // in the actual chairs, the alive players are positions of m * i + b

    const auto mod = [](const auto x, const auto m) {
        const auto res = x % m;
        return res < 0 ? res + m : res;
    };

    for (auto qi = 0; qi < Q; ++qi) {
        char typ;
        ll v;
        cin >> typ >> v;
        cin.ignore();

        if (typ == '+') {
            add = (add + v) % N;
        } else if (typ == '*') {
            // for two players at compressed positions i and j,
            // collision if:
            // ((i * m + b) * mul + add) * v     === ((j * m + b) * mul + add) * v    (mod N)
            // (i * m + b) * mul * v + add * v   === (j * m + b) * mul * v + add * v  (mod N)
            // (i * m + b) * mul * v             === (j * m + b) * mul * v            (mod N)
            // i * m * mul * v                   === j * m * mul * v                  (mod N)
            // i * mul * v                       === j * mul * v         (mod r)  (r * m = N)
            // (i - j) * mul * v === 0  (mod r)
            //       x * mul * v === 0  (mod r)  (-r < x < r)
            // and actually, mul is guaranteed coprime with r
            // since if not, it would have triggered a collision and be reset (to 1). so,
            //             x * v === 0  (mod r)
            // let g = gcd(v, r), then we can divide by g (v' = v/g, r' = r/g):
            //            x * v' === 0  (mod r')
            // v' and r' are coprime, so
            //                 x === 0  (mod r')
            // as -r < x < r, x only has a solution iff r' < r
            // i.e., g > 1

            const auto g = std::gcd(v, r);
            if (g == 1) {
                mul = mul * v % N;
                add = add * v % N;
            } else {
                auto temp_dist = vector(r / g, N);
                auto new_players = vector(r / g, -1);
                const auto new_m = m * g;
                const auto new_b = (b * mul + add) * v % N;
                for (const auto i : views::iota(0, r)) {
                    const auto old_from = (m * i + b) % N;
                    const auto from = (old_from * mul + add) % N;
                    const auto to = from * v % N;
                    const auto j = mod(to - new_b, N) / new_m;
                    const auto d = mod(to - from, N);
                    if (d < temp_dist[j]) {
                        new_players[j] = players[i];
                        temp_dist[j] = d;
                    }
                }
                players = std::move(new_players);
                add = 0;
                mul = 1;
                m = new_m;
                b = new_b;
                r /= g;
            }
        } else {
            // find compressed index i that corresponds to v
            // (m * i + b) * mul + add === v                   (mod N)
            // (m * i + b) * mul       === v - add             (mod N)
            //  m * i * mul            === v - add - b * mul   (mod N)
            //  m * i * mul == K * N   +   v - add - b * mul   (any int K)
            //  m * i * mul == K * r * m + v - add - b * mul   (since r * m = N)
            //      i * mul == K * r   +  (v - add - b * mul) / m
            //      i * mul === (v - add - b * mul) / m        (mod r)
            //             i == (v - add - b * mul) / m * mod_inv(mul, r)

            // for i to exist, (v - add - b * mul) must be divisible be m.
            if ((v - add - b * mul) % m) {
                cout << -1 << '\n';
            } else {
                const auto i = (v - add - b * mul) / m * mod_inverse(mul, r);
                cout << players[mod(i, r)] << '\n';
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
