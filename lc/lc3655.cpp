#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;


// as + bt = gcd(a, b)
int gcd(const int a, const int b, int &s, int &t) {
    s = 1, t = 0;
    int s1 = 0, t1 = 1, r = a, r1 = b;
    while (r1) {
        const auto q = r / r1;
        tie(r, r1) = make_pair(r1, r - q * r1);
        tie(s, s1) = make_pair(s1, s - q * s1);
        tie(t, t1) = make_pair(t1, t - q * t1);
    }
    return r;
}


int mod_inverse(const int a, const int m) {
    int x, y;
    gcd(a, m, x, y);
    return (x % m + m) % m;
}


class Solution {
public:
    int xorAfterQueries(vector<int> &nums, vector<vector<int>> &queries) {
        const auto n = static_cast<int>(nums.size());

        const auto apply = [&](int l, int r, int k, int v) {
            while (l <= r) {
                nums[l] = (1ll * nums[l] * v) % MOD;
                l += k;
            }
        };

        const auto thresh = static_cast<int>(ceil(sqrt(n)));
        // buckets[step][offset] = [..diff array..]
        auto buckets = vector<vector<vector<int>>>();
        buckets.reserve(thresh);
        buckets.emplace_back(); // k = 0
        for (const auto k : views::iota(1, thresh))
            buckets.emplace_back(k, vector((n + k - 1) / k, 1));

        for (const auto &vec : queries) {
            const auto l = vec[0];
            const auto r = vec[1];
            const auto k = vec[2];
            const auto v = vec[3];
            if (k >= thresh) {
                apply(l, r, k, v);
            } else {
                const auto offset = l % k;
                const auto arr_start = l / k;
                const auto arr_end = (r - offset) / k; // inclusive
                auto &diff_arr = buckets[k][offset];
                diff_arr[arr_start] = (1ll * diff_arr[arr_start] * v) % MOD;
                if (arr_end + 1 != diff_arr.size())
                    diff_arr[arr_end + 1] = (1ll * diff_arr[arr_end + 1] * mod_inverse(v, MOD)) % MOD;
            }
        }

        auto vs = vector(n, 1);
        for (const auto k : views::iota(0, thresh)) {
            for (const auto offset : views::iota(0, k)) {
                auto v = 1;
                for (const auto [i, mul] : views::enumerate(buckets[k][offset])) {
                    const auto idx = i * k + offset;
                    if (idx >= n)
                        break;
                    v = (1ll * v * mul) % MOD;
                    vs[idx] = (1ll * vs[idx] * v) % MOD;
                }
            }
        }

        for (const auto [i, v] : views::enumerate(vs)) {
            cout << v << ' ';
            nums[i] = (1ll * nums[i] * v) % MOD;
        }
        cout << endl;

        return reduce(nums.begin(), nums.end(), 0, bit_xor{});
    }
};
