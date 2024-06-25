/*
 *  自己寫的 使用inorder來收集node 之後做相加
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    vector<TreeNode*> v;
    void helper(TreeNode* root) {
        if(!root) return;
        helper(root->right);
        v.push_back(root);
        helper(root->left);
    }
public:
    TreeNode* bstToGst(TreeNode* root) {
        helper(root);
        for(int i = 1; i < v.size(); ++i)
            v[i]->val += v[i - 1]->val;
        return root;
    }
};

/*  
 *  參考 lee215解答
 *  使用一個prev來記錄看過的node其中val的總和
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
    int prev;
public:
    TreeNode* bstToGst(TreeNode* root) {
        if(root->right) bstToGst(root->right);
        prev = root->val = prev + root->val;
        if(root->left) bstToGst(root->left);
        return root;
    }
};
