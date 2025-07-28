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
    const auto [N, M, K] = reads<3>();
    vector<string> grid(N);
    for (auto &row : grid)
        cin >> row;
    cin.ignore();

    auto pfs = vector(N + 1, vector(M + 1, 0));
    for (auto i = 0; i < N; ++i) {
        int row_cnt = 0;
        for (auto j = 0; j < M; ++j) {
            row_cnt += grid[i][j] == 'g';
            pfs[i + 1][j + 1] = pfs[i][j + 1] + row_cnt;
        }
    }

    const int k = K - 1;
    const int tot_g = pfs[N][M];
    int min_loss = tot_g;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            if (grid[i][j] != '.')
                continue;
            int xl = max(0, i - k), yl = max(0, j - k);
            int xr = min(N - 1, i + k), yr = min(M - 1, j + k);
            ++xr;
            ++yr;
            int loss = pfs[xr][yr] - pfs[xl][yr] - pfs[xr][yl] + pfs[xl][yl];
            min_loss = min(min_loss, loss);
        }
    }

    cout << tot_g - min_loss << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
