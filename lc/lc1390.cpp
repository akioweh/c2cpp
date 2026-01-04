#include <bits/stdc++.h>

using namespace std;


auto pfact(const int N) {
    auto res = views::iota(0, N + 1) | ranges::to<vector>(); // smallest prime factor
    for (auto i = 2; i * i <= N; ++i)
        if (res[i] == i) // i is prime
            for (auto j = i * i; j <= N; j += i)
                if (res[j] == j)
                    res[j] = i;
    return res;
}


class Solution {
public:
    int sumFourDivisors(vector<int> &nums) {
        const int maxv = *ranges::max_element(nums);
        const auto spf = pfact(maxv);

        const auto calc = [&](int x) {
            const auto f1 = spf[x];
            if (f1 == x) // x has 0 additional factors
                return 0;
            x /= f1;
            const auto f2 = spf[x];
            x /= f2;
            const auto f3 = spf[x];
            x /= f3;
            if (f1 == f2 && f2 == f3 && x == 1) // x = p^3
                return (1 + f1 + f1 * f1 + f1 * f1 * f1);
            if (f1 != f2 && f3 == 1) // x = p * q
                return (1 + f1 + f2 + f1 * f2);
            return 0;
        };

        const auto rn = ranges::views::transform(nums, calc);
        return accumulate(rn.begin(), rn.end(), 0);
    }
};
