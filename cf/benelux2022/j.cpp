#include <algorithm>
#include <iostream>
#include <random>
#include <ranges>
#include <sstream>
#include <stdexcept>
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


void solve() {
    const auto [W, H] = reads<2, ll>();

    auto cnt = 0;
    string resp;
    const auto ask = [&](const int x, const ll y) {
        if (cnt == 12000)
            throw runtime_error("");
        ++cnt;
        cout << "? " << x << ' ' << y << endl;
        cin >> resp;
        return resp.length() > 5;
    };

    auto perm = views::iota(1, W + 1) | ranges::to<vector<int>>();
    random_device rd;
    mt19937 gen(rd());
    ranges::shuffle(perm, gen);

    const auto brrrrr = [&](const int x, const ll l) {
        const auto rn = views::iota(l + 1, H + 1);
        return (*ranges::partition_point(rn, [&](const auto y) { return ask(x, y); })) - 1;
    };

    auto max_h = 0ll;
    auto max_x = 1;
    for (const auto x : perm) {
        if (!ask(x, max_h + 1))
            continue;
        max_h = brrrrr(x, max_h + 1);
        max_x = x;
        if (max_h == H)
            break;
    }

    cout << "! " << max_x << ' ' << max_h << endl;
}


int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    solve();
    return 0;
}
