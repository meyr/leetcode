/*
 *  必須知道left和right的長度 所以是post-order traversal
 *  答案有可能是把left和right接起來 或是回傳最長的邊讓上邊去接
 *  
 *  similar problem : 687. Longest Univalue Path/
 */

class Solution {
    int ans{};
    int helper(TreeNode* root) {
        if(!root) return 0;
        int l = helper(root->left);
        int r = helper(root->right);
        ans = max(ans, l + r);
        return max(l, r) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        helper(root);
        return ans;
    }
};
