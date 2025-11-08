#pragma GCC optimize("Ofast")

#include <set>
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
    const auto [N, M] = reads<2>();
    const auto dmg = reads();
    const auto hp = reads();
    const auto drop = reads();

    auto good_boys = vector<pair<int, int>>();
    auto bad_boys = vector<int>();
    for (const auto [h, d] : views::zip(hp, drop)) {
        if (d)
            good_boys.emplace_back(h, d);
        else
            bad_boys.push_back(h);
    }
    const auto f_comp = [](const auto a, const auto b) { return a.first < b.first; };
    ranges::sort(good_boys, f_comp);
    ranges::sort(bad_boys);

    auto swords = multiset<int>(dmg.begin(), dmg.end());

    auto res = 0;

    for (const auto [h, d] : good_boys) {
        auto it = swords.lower_bound(h);
        if (it == swords.end())
            break;
        ++res;
        const auto dd = *it;
        if (d > dd) {
            swords.erase(it);
            swords.insert(d);
        }
    }
    for (const auto h : bad_boys) {
        auto it = swords.lower_bound(h);
        if (it == swords.end())
            break;
        ++res;
        swords.erase(it);
    }

    cout << res << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
