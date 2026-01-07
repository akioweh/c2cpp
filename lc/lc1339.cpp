#include <bits/stdc++.h>
#include <ranges>

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
        auto st_sum = unordered_map<void *, int>();

        const function<int(TreeNode *)> dfs = [&](TreeNode *u) {
            if (!u)
                return 0;
            auto res = u->val;
            res += dfs(u->left);
            res += dfs(u->right);
            st_sum[u] = res;
            return res;
        };

        dfs(root);
        const auto tot = st_sum[root];
        auto rn = views::values(st_sum) | views::transform([tot](const auto v) { return 1ll * v * (tot - v); });
        return *ranges::max_element(rn) % MOD;
    }
};
