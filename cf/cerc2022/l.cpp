#include <functional>
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


template<size_t N, typename T = int, bool check_count = true>
array<T, N> reads() {
    array<T, N> arr;
    istringstream iss(read());
    auto r = ranges::copy(views::istream<T>(iss) | views::take(N), arr.begin());
    if (check_count) {
        if (r.out != arr.end())
            throw runtime_error("not enough elements");
        T _;
        if (iss >> _ || !iss.eof())
            throw runtime_error("too many elements");
    }
    return arr;
}


template<typename T>
void writev(const vector<T> &vec) {
    for (const auto v : vec)
        cout << v << ' ';
    cout << '\n';
}


void solve() {
    auto pile = reads();
    ranges::reverse(pile);
    auto a1 = vector<int>({1});
    auto a2 = vector<int>({1});
    auto d1 = vector<int>({100});
    auto d2 = vector<int>({100});
    auto hand = vector<int>();
    auto vs = array<reference_wrapper<vector<int>>, 4>{a1, a2, d1, d2};
    auto ops = array<function<int(int, int)>, 4>{minus<>(), minus<>(), plus<>(), plus<>()};
    auto cmps = array<function<bool(int, int)>, 4>{greater<>(), greater<>(), less<>(), less<>()};

    const auto draw = [&] {
        if (pile.empty())
            return;
        hand.push_back(pile.back());
        pile.pop_back();
    };

    const auto play = [&](const int v, vector<int> &row) {
        row.push_back(v);
        erase(hand, v);
    };

    for (auto _ : views::iota(0, 8))
        draw();

    while (!hand.empty()) {
        // backwards trick
        auto lost = false;
        for (const auto _ : views::iota(0, 2)) { // play twice
            auto played = false;
            for (const auto v : hand) {
                for (auto [vr, op] : views::zip(vs, ops)) {
                    auto &row = vr.get();
                    if (v != op(row.back(), 10))
                        continue;
                    play(v, row);
                    played = true;
                    break;
                }
                if (played)
                    break;
            }
            if (played)
                continue;
            // regular play
            auto min_diff = 101;
            int min_v;
            optional<reference_wrapper<vector<int>>> min_row;
            for (const auto v : hand) {
                for (auto [vr, cmp] : views::zip(vs, cmps)) {
                    auto &row = vr.get();
                    if (!cmp(v, row.back()))
                        continue;
                    auto diff = abs(v - row.back());
                    if (diff < min_diff) {
                        min_diff = diff;
                        min_v = v;
                        min_row = vr;
                    }
                }
            }
            if (min_row.has_value()) {
                play(min_v, min_row.value().get());
                continue;
            }

            // no cards can be played
            lost = true;
            break;
        }

        if (lost)
            break;
        draw(), draw();
    }


    for (auto vr : vs)
        writev(vr.get());
    writev(hand);
    ranges::reverse(pile);
    writev(pile);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
