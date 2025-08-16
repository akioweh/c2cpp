#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>
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


struct br {
    int w;
    vector<br> children;
};

void solve() {
    const auto [W] = reads<1>();

    const function<br()> read_br = [&] {
        const auto [_w, _n] = reads<2>();
        auto res = br{.w = _w};
        for (auto i = 0; i < _n; ++i)
            res.children.push_back(read_br());
        return res;
    };

    auto root = read_br();

    const function<pair<int, int>(br &)> calc = [&](br &branch) {
        // return (n-pieces, remaining trunk weight)
        const auto n = static_cast<int>(branch.children.size());
        auto r_weights = vector<int>(n);
        auto pieces = 0;
        for (auto [child, rw] : views::zip(branch.children, r_weights)) {
            const auto [ch_pieces, r_weight] = calc(child);
            pieces += ch_pieces;
            rw = r_weight;
        }
        pieces += n;
        std::ranges::sort(r_weights);
        auto cur_w = 0;
        for (auto rw : r_weights) {
            if (cur_w + rw > W)
                break;
            --pieces;
            cur_w += rw;
        }
        auto main_w = branch.w;
        main_w += cur_w;
        pieces += main_w / W;
        return make_pair(pieces, main_w % W);
    };

    auto [_res, _r] = calc(root);
    if (_r)
        ++_res;
    cout << _res << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
