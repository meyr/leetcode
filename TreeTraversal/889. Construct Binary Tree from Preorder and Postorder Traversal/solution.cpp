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
/*  2025/02/23 daily challenge
 *  想法一樣
 */
 class Solution {
    unordered_map<int, int> m; // value, index in postorder
    TreeNode* helper(vector<int>& pre, int i, int j, vector<int>& post, int k, int l) {
        if(i >= j || k >= l) return nullptr;
        TreeNode *root = new TreeNode(pre[i]);
        if(i + 1 == j) return root;
        int len = m[pre[i + 1]] - k + 1;
        root->left  = helper(pre, i + 1, i + 1 + len, post, k, k + len);
        root->right = helper(pre, i + len + 1, j, post, k + len, l - 1);
        return root;
    }
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int sz = preorder.size();
        for(int i = 0; i < sz; ++i)
            m[postorder[i]] = i;
        return helper(preorder, 0, sz, postorder, 0, sz);
    }
};
