/* lowest common ancestor 的定義是 我的左樹和右樹分別有看到p和q
 * 所以目前的node為LCA
 *
 * 也就是 left  = lowestCommonAncestor(root->left, p, q);
 *        right = lowestCommonAncestor(root->right, p, q);
 *
 * if(left && right) return root;
 *
 * time  : O(N)
 * space : O(N)
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 基地條件：走到葉子節點，或者找到了 p 或 q
        if (root == nullptr || root == p || root == q) {
            return root;
        }

        // 去左子樹和右子樹找
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // 如果左右子樹都找到了東西，說明 p 和 q 分居兩側，目前節點就是 LCA
        if (left != nullptr && right != nullptr) {
            return root;
        }

        // 如果只有一邊有找到，就回傳有找到的那一邊
        return (left != nullptr) ? left : right;
    }
};
