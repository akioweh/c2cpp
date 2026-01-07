#pragma GCC optimize("Ofast")
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


constexpr int MOD = 1e9 + 7;


class Solution {
public:
    int maxProduct(TreeNode *root) {
        auto sums = vector<int>();

        const auto dfs = [&](this auto &&self, TreeNode *u) {
            if (!u)
                return 0;
            auto res = u->val;
            res += self(u->left);
            res += self(u->right);
            sums.push_back(res);
            return res;
        };

        dfs(root);
        const auto tot = sums.back();
        auto rn = sums | views::transform([tot](const auto v) { return 1ll * v * (tot - v); });
        return *ranges::max_element(rn) % MOD;
    }
};
