/*  從每個node來思考 只要left child或是right child比較深 就回傳較深的那一個
 *  如果兩邊一樣的深度 就回傳當前的root
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    pair<TreeNode*, int> helper(TreeNode* root, int level = 0) {
        if(!root) return {root, level};
        auto [left, lv] = helper(root->left, level + 1);
        auto [right, rv] = helper(root->right, level + 1);
        if(lv == rv) return {root, lv};
        else if(lv > rv) return {left, lv};
        else return {right, rv};
    }
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        auto [rtn, _] = helper(root);
        return rtn;
    }
};
