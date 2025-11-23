#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <functional>
#include <iterator>
#include <limits>
#include <ranges>
#include <type_traits>
#include <vector>


using namespace std;

template<typename U, typename V, typename R, typename F>
concept binary_func = is_invocable_r_v<R, F, U, V>;

template<typename T, typename F>
concept upd_func = is_invocable_r_v<void, F, T &, T, size_t>;


template<size_t N,
         typename T = long long,
         T Default = numeric_limits<T>::min(), // identity for query (e.g., 0 for sum, -INF for max)
         binary_func<T, T, T> auto Func = [](T a, T b) { return max(a, b); }, // fold function (default: max)
         T CacheDefault = T{}, // identity for lazy (default: 0)
         upd_func<T> auto Upd = [](T &a, T b, size_t /*len*/) { a += b; }, // update function (default: add)
         size_t H = bit_width(N)>
struct RURQ {
    array<T, 2 * N> data;
    array<T, N> cache;

    RURQ() {
        ranges::fill(data, Default);
        ranges::fill(cache, CacheDefault);
    }

    // construct from range/iterator
    template<ranges::input_range R>
        requires(same_as<ranges::range_value_t<R>, T> && ranges::sized_range<R>)
    explicit RURQ(const R &&seq) {
        assert(seq.size() == N);
        ranges::fill(cache, CacheDefault);
        ranges::copy(seq, data.begin() + N);
        for (auto i = N; i--;)
            data[i] = Func(data[2 * i], data[2 * i + 1]);
    }

    static size_t node_size(const size_t _i) {
        if (_i >= N)
            return 1ull;
        const auto s = H - bit_width(_i);
        return 1ull << (s + (_i < (N >> s)));
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
        nodes_l.reserve(nodes_l.size() + nodes_r.size());
        ranges::copy(nodes_r | views::reverse, back_inserter(nodes_l));
        return nodes_l;
    }

    // pushes (internal) i's updates to its direct children
    void push1(const size_t _i, const size_t len) {
        if (cache[_i] == CacheDefault)
            return;

        Upd(data[2 * _i], cache[_i], len >> 1);
        Upd(data[2 * _i + 1], cache[_i], len >> 1);
        if (2 * _i < N) {
            cache[2 * _i] += cache[_i];
            cache[2 * _i + 1] += cache[_i];
        }
        cache[_i] = CacheDefault;
    }

    // propagates all updates on path from root to i
    void push(const size_t _i) {
        for (auto s = bit_width(_i); s; --s)
            push1(_i >> s, 1 << s);
    }

    // recomputes nodes on path from i to root
    void pull(size_t _i) {
        size_t len = node_size(_i);
        while (_i >>= 1, len <<= 1) {
            data[_i] = Func(data[2 * _i], data[2 * _i + 1]);
            Upd(data[_i], cache[_i], len);
        }
    }

    void set(const size_t i, const T val) {
        push(i + N);
        data[i + N] = val;
        pull(i + N);
    }

    void update(const size_t l, const size_t r, T val) {
        push(l + N); // necessary if Upd is not commutative
        push(r + N - 1);
        for (const auto i : collect(l, r)) {
            Upd(data[i], val, node_size(i));
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

    // generalized binary search; finds left- or right-most element satisfying pred
    // pred should return true on node's value if target is within node's subtree
    size_t find(const size_t l, const size_t r, const function<bool(T)> pred, const bool reverse) {
        push(l + N);
        push(r + N - 1);

        for (auto i : collect(l, r, reverse)) {
            if (!pred(data[i]))
                continue;
            while (i < N) {
                push1(i, node_size(i));
                const auto nxt = (i << 1) + reverse;
                i = pred(data[nxt]) ? nxt : nxt ^ 1;
            }
            return i - N;
        }
        return r; // not found
    }

    size_t lower_bound(const T value, const size_t l = 0, const size_t r = N) {
        return find(l, r, [&](const T &v) { return v >= value; }, false);
    }
};
