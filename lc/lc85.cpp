#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int maximalRectangle(vector<vector<char>> &matrix) {
        const auto n = static_cast<int>(matrix.size());
        const auto m = static_cast<int>(matrix.front().size());
        auto heights =
                matrix[0] | views::transform([](const auto v) { return v == '1' ? 1 : 0; }) | ranges::to<vector>();

        auto stack = vector<int>();
        stack.reserve(m);
        const auto calc = [&]() {
            heights.push_back(0);
            // monotonic increasing stack
            auto res = 0;
            for (const auto [i, h] : views::enumerate(heights)) {
                while (!stack.empty() && h <= heights[stack.back()]) {
                    const auto h1 = heights[stack.back()];
                    stack.pop_back();
                    const int w = stack.empty() ? i : i - stack.back() - 1;
                    res = max(res, h1 * w);
                }
                stack.push_back(i);
            }
            heights.pop_back();
            stack.pop_back();
            return res;
        };

        auto ans = calc();
        for (auto i = 1; i < n; ++i) {
            for (auto [ch, hv] : views::zip(matrix[i], heights))
                hv = ch == '1' ? hv + 1 : 0;
            ans = max(ans, calc());
        }
        return ans;
    }
};
