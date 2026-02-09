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
/*  2026/02/09 daily challenge
 *  想法和上面一樣 但是少考慮了重用原本的node來減少 allocate memory
 */
class Solution {
    void inorder(TreeNode* root, vector<int>& values) {
        if(!root) return;
        inorder(root->left, values);
        values.push_back(root->val);
        inorder(root->right, values);
    }
    TreeNode* helper(const vector<int>& values, int i, int j) {
        if(i > j) return nullptr;
        else {
            int m = (i + j) / 2;
            return  new TreeNode(values[m],
                                 helper(values, i, m - 1),
                                 helper(values, m + 1, j));
        }
    }
public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> values;
        inorder(root, values);
        return helper(values, 0, values.size() - 1);
    }
};
