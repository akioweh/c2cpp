// #pragma GCC optimize("Ofast,unroll-loops,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <climits>
#include <cstddef>
#include <functional>
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


vector<int> trip_merge(const vector<int> &a, const vector<int> &b, const vector<int> &c) {
    vector<int> res;
    size_t i = 0, j = 0, k = 0;
    int prev = INT_MIN;
    bool ii = true, jj = true, kk = true;

    while (ii || jj || kk) {
        int min_v = INT_MAX;
        if (ii)
            min_v = min(min_v, a[i]);
        if (jj)
            min_v = min(min_v, b[j]);
        if (kk)
            min_v = min(min_v, c[k]);

        if (min_v != prev) {
            res.push_back(min_v);
            prev = min_v;
        }

        if (ii && a[i] == min_v)
            ++i;
        if (jj && b[j] == min_v)
            ++j;
        if (kk && c[k] == min_v)
            ++k;
        ii = i < a.size();
        jj = j < b.size();
        kk = k < c.size();
    }

    return res;
}


void solve() {
    const auto [N_ig, S, M, D, N_bad] = reads<5>();
    const auto brands = reads();
    vector<vector<int>> starters(S, vector<int>()), mains(M, vector<int>()), desserts(D, vector<int>());
    for (auto &vref : {ref(starters), ref(mains), ref(desserts)}) {
        for (auto &v : vref.get()) {
            auto tmp = reads();
            tmp.erase(tmp.begin());
            for (auto &i : tmp)
                --i;
            ranges::sort(tmp);
            v = tmp;
        }
    }
    vector<vector<bool>> no_sm(S, vector(M, false)), no_md(M, vector(D, false)), no_sd(S, vector(D, false));
    for (auto i = 0; i < N_bad; ++i) {
        auto [a, b] = reads<2>();
        if (b < a)
            swap(a, b);
        --a;
        --b;
        if (a < S) {
            if (b < S + M)
                no_sm[a][b - S] = true;
            else
                no_sd[a][b - S - M] = true;
        } else {
            no_md[a - S][b - S - M] = true;
        }
    }

    unsigned long long ans = 0;
    bool flown = false;
    for (const auto [si, s] : views::enumerate(starters)) {
        for (const auto [mi, m] : views::enumerate(mains)) {
            for (const auto [di, d] : views::enumerate(desserts)) {
                if (no_sm[si][mi] || no_sd[si][di] || no_md[mi][di])
                    continue;
                unsigned long long brand_comps = 1;
                for (const auto b : trip_merge(s, m, d)) {
                    const auto bv = static_cast<unsigned long long>(brands[b]);
                    if (brand_comps > ULLONG_MAX / bv) {
                        brand_comps = 0;
                        break;
                    }
                    brand_comps *= bv;
                }
                if (!brand_comps || ans > ULLONG_MAX - brand_comps) {
                    flown = true;
                    break;
                }
                ans += brand_comps;
            }
            if (flown)
                break;
        }
        if (flown)
            break;
    }

    if (flown || ans > 1'000'000'000'000'000'000) {
        cout << "too many" << endl;
    } else {
        cout << ans << endl;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
