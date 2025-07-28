#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


template<typename T = int>
vector<T> reads() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    return {istream_iterator<T>(iss), istream_iterator<T>()};
}


template<size_t N, typename T = int>
array<T, N> reads() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    array<T, N> arr{};
    auto r = ranges::copy(
        views::istream<T>(iss) | views::take(N),
        arr.begin()
    );
    if (r.out != arr.end()) { throw runtime_error("not enough elements"); }
    return arr;
}


bool perm_parity(const vector<int> &p) {
    bool odd = false;
    vector seen(p.size(), false);
    for (const auto i : views::iota(0ull, p.size())) {
        if (seen[i]) continue;
        seen[i] = true;
        int next = p[i];
        int cycle_size = 1;
        while (next != i) {
            seen[next] = true;
            next = p[next];
            cycle_size++;
        }
        if (cycle_size % 2 == 0)
            odd = !odd;
    }
    return odd;
}


void solve() {
    // clearly it's two independent subsets partitioned by index parity
    // then clearly it is trivial to obtain a 3-cycle in each subset (assuming at least 3+2 elements)
    // so each partition can achieve any even permutation (with some edge cases when N < 6)
    // or both achieve odd permutations
    // actually the edge cases will take care of themselves (i think) if we just
    // sort first and adjust for parity afterwards
    auto [N] = reads<1, int>();
    const auto ns = reads<int>();

    vector<int> odds(N / 2), evens((N + 1) / 2);
    ranges::iota(evens, 0);
    ranges::iota(odds, 0);
    ranges::sort(evens, {}, [&](const int i) { return ns[2 * i]; });
    ranges::sort(odds, {}, [&](const int i) { return ns[1 + 2 * i]; });

    vector<int> res(N);
    for (const auto i : views::iota(0, N))
        res[i] = i % 2 == 0 ? ns[evens[i / 2] * 2] : ns[odds[i / 2] * 2 + 1];

    if (perm_parity(evens) != perm_parity(odds))
        swap(res[N - 1], res[N - 3]);  // fix parity

    for (const auto i : res)
        cout << i << ' ';
    cout << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [T] = reads<1, int>();
    while (T--) {
        solve();
    }
    return 0;
}
