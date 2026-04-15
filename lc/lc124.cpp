#include <bits/stdc++.h>

using namespace std;

/**
 * Definition for a binary tree node.
 */
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
    int maxPathSum(TreeNode *root) {
        auto res = numeric_limits<int>::min();

        const auto dfs = [&res](this auto &&self, const TreeNode *u) {
            if (u == nullptr)
                return 0;
            const auto l = self(u->left);
            const auto r = self(u->right);
            const auto v = max({l, r, 0}) + u->val;
            res = max({res, v, l + r + u->val});
            return v;
        };

        dfs(root);
        return res;
    }
};
