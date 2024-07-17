/*
 *  因為要刪掉to_delete的node 所以最好是從底部往上搜尋 --> post-order
 *  另外自己是屬於to_delete也要刪掉 所以回傳nullptr
 *
 *  time  : O(N + M), N : size of tree, M : size of to_delete
 *  space : O(N + M), worest case tree連成一排 stack大小正比於N
 */

class Solution {
    TreeNode* helper(TreeNode* root, unordered_set<int>& del, vector<TreeNode*>& rtn) {
        if(!root) return root;
        root->left = helper(root->left, del, rtn);
        root->right = helper(root->right, del, rtn);
        if(del.count(root->val)) {
            if(root->left) rtn.push_back(root->left);
            if(root->right) rtn.push_back(root->right);
            return nullptr; // 還傳nullptr刪掉自己
        } else return root;
    }
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int> del(begin(to_delete), end(to_delete)); // O(M)
        vector<TreeNode*> rtn;
        helper(root, del, rtn); // O(N)
        if(!del.count(root->val)) rtn.push_back(root);
        return rtn;
    }
};
