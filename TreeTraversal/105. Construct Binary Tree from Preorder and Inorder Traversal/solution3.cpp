/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    unordered_map<int, int> m;
    TreeNode* helper(vector<int>& pre, int i, int j, vector<int>& ino, int k, int l) {
        if(i >= j || k >= l) return nullptr;
        int idx = m[pre[i]];
        int len = idx - k;
        return new TreeNode(pre[i], 
                            helper(pre, i + 1, i + 1 + len, ino, k, idx),
                            helper(pre, i + 1 + len, j, ino, idx + 1, l));
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for(int i = 0; i < inorder.size(); ++i)
            m[inorder[i]] = i;
        return helper(preorder, 0, preorder.size(), inorder, 0, inorder.size());
    }
};
