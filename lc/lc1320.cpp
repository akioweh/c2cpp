#include <bits/stdc++.h>

using namespace std;

// clang-format off
constexpr array GRID = {
    "ABCDEF"sv,
    "GHIJKL"sv,
    "MNOPQR"sv,
    "STUVWX"sv,
    "YZ"sv
};
// clang-format on

// for some reason std::abs() is having trouble being constexpr
template<typename T>
constexpr T cabs(T x) {
    return x > 0 ? x : -x;
}

// the 27-th "letter" is "hover"; when the finger has not pressed anything yet;
constexpr auto DIST = []() consteval {
    auto coords = array<pair<int, int>, 26>{};
    for (const auto [x, s] : views::enumerate(GRID)) {
        for (const auto [y, c] : views::enumerate(s))
            coords[c - 'A'] = {x, y};
    }

    const auto dist = [&](int a, int b) {
        const auto [ax, ay] = coords[a];
        const auto [bx, by] = coords[b];
        return cabs(ax - bx) + cabs(ay - by);
    };

    auto res = array<array<int, 27>, 27>{};
    for (const auto [a, b] : views::cartesian_product(views::iota(0, 26), views::iota(0, 26)))
        res[a][b] = dist(a, b);
    ranges::fill(res[26], numeric_limits<int>::max() / 2);
    return res;
}();


template<typename T>
constexpr auto minimize(T &var, const T &val) {
    var = min(var, val);
}


class Solution {
public:
    int minimumDistance(string word) {
        const auto n = static_cast<int>(word.length());

        // dp[i][c] = min cost to type word[:i] with the _other_ finger on letter c
        // then, min cost to type word[:i] is min(dp[i])...
        // or: min(dp[i-1][c] + min(dist(word[i-2], word[i-1]), dist(word[i-2], c))  for c in alphabet)
        // push-based dp should make more sense

        // the 27-th "letter" is "hover"; when the finger has not pressed anything yet;
        auto dp = vector(n + 1, vector(27, numeric_limits<int>::max() / 2));
        dp[0].assign(27, 0);

        for (const auto i : views::iota(0, n)) {
            const auto nxt_c = word[i] - 'A';
            const auto cur_c = i ? word[i - 1] - 'A' : nxt_c;
            for (const auto [c, cost] : views::enumerate(dp[i])) {
                // keep using same finger
                minimize(dp[i + 1][c], cost + DIST[cur_c][nxt_c]);
                // use other finger
                minimize(dp[i + 1][cur_c], cost + DIST[c][nxt_c]);
            }
        }

        return *ranges::min_element(dp.back());
    }
};
