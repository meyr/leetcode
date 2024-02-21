/*
    類似105. Construct Binary Tree from Preorder and Inorder Traversal
*/
class Solution {
    TreeNode* helper(vector<int>& in, int i, int j, vector<int>& post, int k, int l) {
        if(i >= j) return nullptr;
        else {
            int idx = m[post[l - 1]];
            int len = idx - i;
            return new TreeNode(post[l - 1], 
                                helper(in, i, idx, post, k, k + len),
                                helper(in, idx + 1, j, post, k + len, l - 1));
        }
    }
    unordered_map<int, int> m;
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for(int i = 0; i < inorder.size(); ++i)
            m[inorder[i]] = i;
        return helper(inorder, 0, inorder.size(), postorder, 0, postorder.size());
    }
};
