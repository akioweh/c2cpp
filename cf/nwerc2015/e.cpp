// #pragma GCC optimize("Ofast,unroll-loops,inline")
// #pragma GCC target("avx,avx2,fma,bmi,bmi2,popcnt,lzcnt")

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <set>
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
    vector<pair<int, int>> nums(N);
    for (auto &p : nums) {
        p = reads<2>();
    }

    vector<array<int, 3>> outs_arr(N);
    map<int, vector<int>> outs_map;
    for (const auto [i, p] : views::enumerate(nums)) {
        const auto pf = p.first, ps = p.second;
        outs_map[pf * ps].push_back(i);
        outs_map[pf + ps].push_back(i);
        outs_map[pf - ps].push_back(i);
        outs_arr[i] = {pf * ps, pf + ps, pf - ps};
    }

    if (outs_map.size() < N) {
        cout << "impossible" << endl;
        return;
    }

    map<int, int> asdf;
    for (const auto &[k, v] : outs_map)
        asdf[k] = v.size();
    vector<pair<int, int>> pq(asdf.size());
    for (auto &[v, cnt] : asdf)
        pq.emplace_back(cnt, v);
    ranges::make_heap(pq);

    vector<int> ans(N);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
