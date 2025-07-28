// #pragma GCC optimize("Ofast,unroll-loops,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


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
    const auto [N] = reads<1>();
    auto player = reads();
    const auto dealer = reads();

    // to have a score of K, the game goes through
    // the first K and first N-K of the player's and dealer's cards, respectively
    // --> min(player[:K]) > min(dealer[:N-K])
    // **clearly** /s, the answer is monotonic and the minification is greedy

    vector<int> pfmin(N);
    vector<int> sfmax(N);
    int cur_min_idx = 0;
    int cur_min = player[cur_min_idx];
    for (auto i = 0; i < N; ++i) {
        if (player[i] < cur_min) {
            cur_min = player[i];
            cur_min_idx = i;
        }
        pfmin[i] = cur_min_idx;
    }
    int cur_max_idx = N - 1;
    int cur_max = player[cur_max_idx];
    for (auto i = N; --i;) {
        if (player[i] > cur_max) {
            cur_max = player[i];
            cur_max_idx = i;
        }
        sfmax[i] = cur_max_idx;
    }

    const auto play = [&] {
        int score = 0;
        auto p_it = player.cbegin();
        auto d_it = dealer.cbegin();
        for (auto i = 0; i < N; ++i) {
            if (*p_it > *d_it) {
                ++score;
                ++p_it;
            } else {
                ++d_it;
            }
        }
        return score;
    };

    const int def = play();

    const auto check = [&](const int k) {
        if (k == 0)
            return true;
        if (k == N)
            return def == N;
        if (k > N)
            return false;
        const auto min_idx = pfmin[k - 1];
        const auto max_idx = sfmax[k];
        auto &pl = player[min_idx];
        auto &pr = player[max_idx];
        if (pl < pr)
            swap(pl, pr);
        bool res = play() >= k;
        if (pr < pl)
            swap(pl, pr);
        return res;
    };

    const auto r = views::iota(def, N + 2);
    const auto it = ranges::upper_bound(r, false, equal_to(), check);
    cout << *it - 1 << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
