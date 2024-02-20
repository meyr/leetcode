class Solution {
    TreeNode* helper(vector<int>& pre, int i, int j, vector<int>& ino, int k, int l) {
        if(i == j) return nullptr;
        TreeNode* root = new TreeNode(pre[i]);
        if(i + 1 == j) return root;
        int idx = k;
        while(ino[idx] != pre[i]) ++idx;
        int len1 = idx - k;
        int len2 = l - idx;
        root->left = helper(pre, i + 1, i + 1 + len1, ino, k, idx);
        root->right = helper(pre, i + 1 + len1, j, ino, idx + 1, l);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return helper(preorder, 0, preorder.size(), inorder, 0, inorder.size());
    }
};
