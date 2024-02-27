/*
 *  因為必須知道left和right的長度 所以使用post-order
 *
 *  similar problem : 543. Diameter of Binary Tree
 */

class Solution {
    int ans{};
    int helper(TreeNode* root) {
        if(!root) return 0;
        int l = helper(root->left);
        int r = helper(root->right);
        // left和right的長度會因為root->val而改變
        if(root->left && root->left->val == root->val) l++;
        else l = 0;
        if(root->right && root->right->val == root->val) r++;
        else r = 0;
        // left和right連接的情況
        int connect = root->left && root->right && root->left->val == root->val && root->right->val == root->val ? 
            l + r : 0;
        ans = max({ans, l, r, connect});
        // 只回傳left或right最長的那一邊
        return max(l, r);
    }
public:
    int longestUnivaluePath(TreeNode* root) {
        helper(root);
        return ans;
    }
};
