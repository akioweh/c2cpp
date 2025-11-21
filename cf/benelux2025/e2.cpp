#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,sse4.2,fma,bmi2,popcnt")

#include <algorithm>
#include <array>
#include <cassert>
#include <coroutine>
#include <generator>
#include <iostream>
#include <limits>
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


struct TN {
    bool end{};
    array<TN *, 26> nxt{};
};


using eoff = tuple<ll, ll, bool>;


void solve() {
    const auto [N] = reads<1>();
    const auto order = reads<ll>();
    const auto duration = reads<ll>();

    constexpr auto L = 1000000ll;

    // relative distance between two states
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

    // state @ time -> absolute offset
    const auto state_to_offset = [&](ll t, ll f, bool d) {
        auto t_at_0 = t - dist(0, true, f, d);
        return (t_at_0 % 2 * L + 2 * L) % 2 * L;
    };

    // state @ time -> state @ some other time
    const auto pos_at_t = [](const eoff &anchor, ll at_t) -> pair<ll, bool> {
        auto [t, f, d] = anchor;
        at_t %= 2 * L;
        t %= 2 * L;
        if (t > at_t) {
            swap(t, at_t);
            d = !d;
        }

        auto diff = at_t - t;
        while (diff) {
            const auto dist_to_bounce = d ? (L - f) : f;
            if (diff >= dist_to_bounce) {
                diff -= dist_to_bounce;
                f = d ? L : 0ll;
                d = !d;
            } else {
                f += d ? diff : -diff;
                diff = 0;
            }
        }

        return {f, d};
    };

    const auto simulate = [&](vector<eoff> &eoffs) -> ll {
        const auto next_soonest = [&](const ll now_t, const ll now_f, const bool now_dir) -> ll {
            auto min_wait = numeric_limits<ll>::max();
            for (const auto &anchor : eoffs) {
                const auto [f, dir] = pos_at_t(anchor, now_t);
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
            const auto wait_until = next_soonest(cur_time, cur_floor, needed_dir);
            cur_time = wait_until + abs(nxt_floor - cur_floor) + duration[i];
        }
        return cur_time;
    };

    // time of arrival
    const auto tor = [&](const eoff &anchor, const ll target_f, const bool target_d) -> ll {
        auto t = 0ll;
        auto [f, d] = pos_at_t(anchor, 0);
        if (d != target_d) {
            const auto mid = d ? L : 0;
            t += abs(mid - f);
            f = mid;
            d = !d;
        }

        if ((target_f > f) == d) {
            return t + abs(target_f - f);
        }
        return 2 * L - abs(target_f - f);
    };

    // A <- B <- C <- D
    //
    // A <- B <- C
    //      ^-------- D
    //
    // A <- B <- C
    // ^------------- D
    //
    // A <- B
    // ^-------- C <- D
    //
    // A <- B <------ D
    // ^-------- C
    //
    // A <- B
    // ^-------- C
    // ^------------- D

    auto res = numeric_limits<ll>::max();
    const auto A = eoff{0, 0, true};

    for (const auto i : views::iota(0, N)) {
        const auto prev_floor = i ? order[i - 1] : 0ll;
        const auto floor = order[i];
        const auto delay = duration[i];
        const auto _dir = floor > prev_floor;
        const auto t = tor({0, 0, true}, floor, _dir);
        const auto finish_t = t + delay;
        for (const auto &B : {eoff{t + finish_t, floor, true}, eoff{t + finish_t, floor, false}}) {
            for (const auto i : lol()) {
                // asdf
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
