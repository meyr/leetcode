/*
 *    因為是binary search tree，且要找lowest common ancestor
 *    當我一層一層往下，找到small < root->val < larget
 *    即為lowest common ancestor
 */
 
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int small = min(p->val, q->val);
        int large = max(p->val, q->val);
        while(root) {
            if(root->val > large) root = root->left;
            else if(root->val < small) root = root->right;
            else return root;
        }
        return nullptr;
    }
};
