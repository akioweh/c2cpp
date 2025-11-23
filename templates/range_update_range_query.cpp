#include <algorithm>
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

template<typename F, typename U, typename V, typename R>
concept binary_func = is_invocable_r_v<R, F, U, V>;

template<typename F, typename T, typename U>
concept upd_func = is_invocable_r_v<void, F, T &, const U &, size_t>;


template<typename T = long long, // output/base type
         typename U = T, // "update" type
         T Default = numeric_limits<T>::min(), // identity for query (e.g., 0 for sum, -INF for max)
         binary_func<T, T, T> auto Func = [](T a, T b) { return max(a, b); }, // fold function (default: max)
         U CacheDefault = U{}, // identity for lazy (default: 0)
         upd_func<T, U> auto Upd = [](T &a, U &b, size_t /*len*/) { a += b; } // update function (def: add)
         >
struct RURQ {
    size_t N;
    size_t H;
    vector<T> data;
    vector<U> cache;

    RURQ(const size_t n) : N(n), H(bit_width(n)), data(2 * n, Default), cache(n, CacheDefault) {}

    // construct from range/iterator
    template<ranges::input_range R>
        requires(same_as<ranges::range_value_t<R>, T> && ranges::sized_range<R>)
    explicit RURQ(R &&seq) :
        N(ranges::size(seq)), H(bit_width(ranges::size(seq))), cache(ranges::size(seq), CacheDefault) {
        data.resize(2 * N);
        ranges::copy(seq, data.begin() + N);
        for (auto i = N; i--;)
            data[i] = Func(data[2 * i], data[2 * i + 1]);
    }

    // calculates the length of node
    [[nodiscard]] size_t node_size(const size_t _i) const {
        if (_i >= N)
            return 1ull;
        const auto s = H - bit_width(_i);
        return 1ull << (s + (_i < (N >> s)));
    }

    // collects the exact nodes representing the range [l, r), in order
    [[nodiscard]] vector<size_t> collect(size_t l, size_t r, const bool reverse = false) const {
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

    void update(const size_t l, const size_t r, U val) {
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

    T query(const size_t l, const size_t r) {
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

    size_t lower_bound(const T value, const size_t l, const size_t r) {
        return find(l, r, [&](const T &v) { return v >= value; }, false);
    }
};
