#pragma GCC optimize("Ofast")

#include <vector>
#pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")
#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
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


struct TN {
    bool end{};
    array<TN *, 26> nxt{};
};


void solve() {
    const auto [N] = reads<1>();
    const auto order = reads<ll>();
    const auto duration = reads<ll>();

    constexpr auto L = 1000000ll;

    const auto dist = [](const ll src_f, const bool src_d, const ll end_f, const bool end_d) -> ll {
        if (src_d == end_d) { // eithe two bounces or zero
            if ((end_f > src_f) == src_d)
                return abs(end_f - src_f);
            return 2 * L - abs(end_f - src_f);
        }
        // one bounce
        const auto mid = src_d ? L : 0ll;
        return abs(src_f - mid) + abs(end_f - mid);
    };

    const auto simulate = [&](vector<int> T) -> ll {
        ranges::sort(T, greater{});
        auto usable = vector<tuple<ll, ll, bool>>(); // (start_t, start_f, direc)
        usable.emplace_back(0, 0, true);

        const auto next_soonest = [&](const ll now_t, const ll now_f, const bool now_dir) -> ll {
            auto min_wait = numeric_limits<ll>::max();
            for (const auto &[start_t, start_f, start_d] : usable) {
                assert(now_t >= start_t);
                auto diff = now_t - start_t;
                diff %= 2 * L;
                auto dir = start_d;
                auto f = start_f;
                while (diff) {
                    const auto dist_to_bounce = dir ? (L - f) : f;
                    if (diff >= dist_to_bounce) {
                        diff -= dist_to_bounce;
                        f = dir ? L : 0ll;
                        dir = !dir;
                    } else {
                        f += dir ? diff : -diff;
                        diff = 0;
                    }
                }
                assert(0 <= f && f <= L);
                min_wait = min(min_wait, dist(f, dir, now_f, now_dir));
            }
            assert(min_wait >= 0);
            return min_wait + now_t;
        };

        auto cur_time = 0ll;
        auto cur_floor = 0;
        for (const auto i : views::iota(0, N)) {
            const auto nxt_floor = order[i];
            const auto needed_dir = nxt_floor > cur_floor;
            if (!T.empty() && T.back() == i) {
                T.pop_back();
                usable.emplace_back(cur_time, cur_floor, needed_dir);
            }
            const auto wait_until = next_soonest(cur_time, cur_floor, needed_dir);
            cur_time = wait_until + abs(nxt_floor - cur_floor) + duration[i];
        }
        return cur_time;
    };


    auto res = simulate({});
    for (const auto i : views::iota(1, N)) {
        res = min(res, simulate({i}));
        for (const auto j : views::iota(i + 1, N)) {
            res = min(res, simulate({i, j}));
            for (const auto k : views::iota(j + 1, N)) {
                res = min(res, simulate({i, j, k}));
            }
        }
    }

    cout << res << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
