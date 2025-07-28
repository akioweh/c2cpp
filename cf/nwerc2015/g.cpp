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

    const auto readsm1 = []() {
        auto res = reads();
        for (auto &v : res)
            --v;
        return res;
    };
    const auto a = readsm1();
    const auto b = readsm1();
    const auto c = readsm1();

    vector<int> aux(N);
    const function<ll(vector<int> &, int, int)> brrr = [&brrr, &aux](vector<int> &arr, const int l, const int r) -> ll {
        if (l + 1 == r)
            return 0;
        const auto m = (l + r) / 2;
        const auto ivs_l = brrr(arr, l, m);
        const auto ivs_r = brrr(arr, m, r);
        ll ivs_m = 0;
        int li = l, ri = m, k = 0;
        while (li < m && ri < r) {
            if (arr[li] < arr[ri]) {
                aux[k++] = arr[li++];
            } else {
                aux[k++] = arr[ri++];
                ivs_m += m - li;
            }
        }
        while (li < m)
            aux[k++] = arr[li++];
        while (ri < r)
            aux[k++] = arr[ri++];

        ranges::copy_n(aux.begin(), r - l, arr.begin() + l);
        return ivs_l + ivs_m + ivs_r;
    };

    ll invs = 0;

    // normalize against a
    vector<int> t(N);
    for (auto [u, v] : views::enumerate(a))
        t[v] = u;
    auto b2 = b, c2 = c;
    for (auto &v : b2)
        v = t[v];
    for (auto &v : c2)
        v = t[v];

    invs += brrr(b2, 0, N);
    invs += brrr(c2, 0, N);

    // normalize against b
    for (auto [u, v] : views::enumerate(b))
        t[v] = u;
    c2 = c;
    for (auto &v : c2)
        v = t[v];

    invs += brrr(c2, 0, N);

    ll ans = static_cast<ll>(N) * (N - 1) / 2;
    ans -= invs / 2;
    cout << ans << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
