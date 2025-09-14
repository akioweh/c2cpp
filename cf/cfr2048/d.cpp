#pragma GCC optimize("Ofast")

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <type_traits>
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

template<typename U, typename V, typename R, typename F>
concept binary_func = is_invocable_r_v<R, F, U, V>;

template<typename T, typename F>
concept upd_func = is_invocable_r_v<void, F, T &, T, size_t>;

template<typename... Ts>
auto nsum(const Ts &...a) {
    return (a + ...);
}

template<typename T,
         size_t N,
         T Default = 0,
         binary_func<T, T, T> auto Func = [](T a, T b) { return max(a, b); }, // default: max
         T CacheDefault = 0,
         upd_func<T> auto Upd = [](T &a, T b, size_t /*len*/) { a += b; } // default: addition  (&T, T, int) -> void
         >
struct RURQ {
    array<T, 2 * N> data;
    array<T, N> cache;

    // construct from range/iterator
    template<ranges::input_range R>
        requires same_as<ranges::range_value_t<R>, T>
    explicit RURQ(const R &&seq) {
        assert(seq.size() == N);
        ranges::fill(cache, CacheDefault);
        ranges::copy(seq, data.begin() + N);
        for (auto i = N; i-- > 0;)
            data[i] = Func(data[2 * i], data[2 * i + 1]);
    }


    // pushes (internal) node i's updates to its direct children
    void push1(const size_t i) {
        if (!cache[i])
            return;
        cache[i] = CacheDefault;
        Upd(data[2 * i], cache[i], 1);
        Upd(data[2 * i + 1], cache[i], 1);
        if (2 * i < N) {
            cache[2 * i] += cache[i];
            cache[2 * i + 1] += cache[i];
        }
    }


    // propagates all updates on path from root to node i
    void push(const size_t i) {
        for (auto s = bit_width(i); s > 0; s--) {
            push1(i >> s);
        }
    }


    // full propagation (push all lazy to leaves)
    void propagate() {
        for (auto i = 1; i < N; i++)
            push(i);
    }


    // recomputes internal nodes on path from i to root
    void pull(size_t i) {
        while (i /= 2) {
            data[i] = Func(data[2 * i], data[2 * i + 1]);
            Upd(data[i], cache[i], 1);
        }
    }


    // collects the exact nodes representing the range [l, r), in order
    static vector<size_t> collect(size_t l = 0, size_t r = N, const bool reverse = false) {
        vector<size_t> nodes_l, nodes_r;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                nodes_l.push_back(l++);
            if (r & 1)
                nodes_r.push_back(--r);
        }
        if (reverse)
            swap(nodes_l, nodes_r);
        nodes_l.insert(nodes_l.end(), nodes_r.rbegin(), nodes_r.rend());
        return nodes_l;
    }


    void set(const size_t i, const T val) {
        push(i + N);
        data[i + N] = val;
        pull(i + N);
    }


    void update(const size_t l, const size_t r, T val) {
        for (auto i : collect(l, r)) {
            Upd(data[i], val, 1);
            if (i < N)
                cache[i] += val;
        }
        pull(l + N);
        pull(r + N - 1);
    }


    T query(const size_t l = 0, const size_t r = N) {
        push(l + N);
        push(r + N - 1);
        return ranges::fold_left(collect(l, r) | views::transform([this](const auto i) { return data[i]; }), Default,
                                 Func);
    }


    size_t bound(
            const T value, const size_t l, const size_t r, const binary_func<T, T, bool> auto cmp, const bool reverse) {
        push(l + N);
        push(r + N - 1);
        for (auto i : collect(l, r, reverse)) {
            if (cmp(data[i], value)) {
                while (i < N) {
                    push1(i);
                    auto nxt = 2 * i + reverse;
                    if (cmp(data[nxt], value))
                        i = nxt;
                    else
                        i = nxt ^ 1;
                }
                return i - N;
            }
        }
        return reverse ? l : r;
    }


    size_t lower_bound(const T value, const size_t l = 0, const size_t r = N) {
        return bound(value, l, r, less{}, false);
    }


    size_t upper_bound(const T value, const size_t l = 0, const size_t r = N) {
        return bound(value, l, r, less_equal{}, false);
    }
};

void solve() {
    const auto [N, Q] = reads<2>();
    const auto arr = reads();
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto [t] = reads<1>();
    while (t--)
        solve();
    return 0;
}
