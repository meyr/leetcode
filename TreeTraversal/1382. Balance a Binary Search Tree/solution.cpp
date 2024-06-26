/*
 *  沒什麼比較好的方法
 *  1. 先用inorder把BST讀取出來
 *  2. 重新建構balanced BST 
 *
 *  time  : O(N) step1, step2都只會讀取一次node
 *  space : O(N)
 */
class Solution {
    void inorder(TreeNode* root) {
        if (!root) return;
        inorder(root->left);
        v.push_back(root);
        inorder(root->right);
    }
    TreeNode* helper(int i, int j) {
        if (i > j) return nullptr;
        int m = (i + j) / 2;
        v[m]->left = helper(i, m - 1);
        v[m]->right = helper(m + 1, j);
        return v[m];
    }
    vector<TreeNode*> v;
public:
    TreeNode* balanceBST(TreeNode* root) {
        inorder(root);
        return helper(0, v.size() - 1);
    }
};
