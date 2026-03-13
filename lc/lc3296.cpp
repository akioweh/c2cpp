#include <bits/stdc++.h>
#include <limits>

using namespace std;

class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int> &workerTimes) {
        // sum = (n + 1) / 2 * n
        // need find: largest n s.t. sum <= S
        // (n + 1) / 2 * n <= S
        // (n^2 + n) / 2 <= S
        // n^2 + n <= 2 * S
        // n^2 + n - 2 * S <= 0
        // n <= (-1+sqrt(1+8S))/2
        // n == floor( (sqrt(1+8S)-1) / 2 )
        const auto check = [&](const auto max_time) {
            auto rem = mountainHeight;
            for (const auto w : workerTimes) {
                const auto n = floor((sqrt(1 + 8 * (max_time / w)) - 1) / 2);
                rem -= n;
                if (rem <= 0)
                    return true;
            }
            return false;
        };

        auto rn = views::iota(0ull, numeric_limits<uint64_t>::max());
        auto it = ranges::partition_point(rn, not_fn(check));
        return *it;
    }
};
