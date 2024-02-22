class Solution {
    unordered_map<int, int> m;
    TreeNode* helper(vector<int>& pre, int i, int j, vector<int>& post, int k, int l) {
            if (i > j) return nullptr;
            int len = i < j ?  m[pre[i + 1]] - k + 1 : 0;
            return new TreeNode(pre[i],
                helper(pre, i + 1, i + len, post, k, k + len - 1),
                helper(pre, i + len + 1, j, post, k + len, l - 1));
    }
public:
    TreeNode *constructFromPrePost(vector<int> &preorder, vector<int> &postorder) {
        int sz = preorder.size();
        for (int i = 0; i < sz; i++)
            m[postorder[i]] = i;
        
        return helper(preorder, 0, sz - 1, postorder, 0, sz - 1);
    }
};
