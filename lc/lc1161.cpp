#include <algorithm>
#include <bits/stdc++.h>

using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    int maxLevelSum(TreeNode *root) {
        auto sums = vector({numeric_limits<int>::min()});
        auto cur_lvl = vector({root});
        while (!cur_lvl.empty()) {
            auto nxt_lvl = vector<TreeNode *>();
            auto cur_sum = 0;
            for (const auto n_ptr : cur_lvl) {
                cur_sum += n_ptr->val;
                if (n_ptr->left)
                    nxt_lvl.push_back(n_ptr->left);
                if (n_ptr->right)
                    nxt_lvl.push_back(n_ptr->right);
            }
            sums.push_back(cur_sum);
            cur_lvl = std::move(nxt_lvl);
        }
        const auto m = *ranges::max_element(sums);
        for (const auto [i, v] : views::enumerate(sums)) {
            if (v == m)
                return i;
        }
        std::unreachable();
    }
};
