/*                                                root->val - 1 + left + right
                                                                 ^^^^^ left child 的需求
                                                                        ^^^^^^^ right child 的需求
        root            對root來說有六種可能, 1. 多餘的coins往上parent       4. coins從parent移動過來
                                             2. 多餘的coins往left child    5. coins從left child移動過來
    left     right                           3. 多餘的coins往right child   6. coins從right child移動過來

                        
                        對child來說有兩種情況 left = dfs(root->val) > 0 有多的從child移動到parent
                                                                   < 0 必須把多餘的coins往child移動 

    time  : O(N)  每個node都走過一次
    space : O(N)  stack的深度，最worse case全部都串再一起
*/

class Solution {
    int res{};
    int dfs(TreeNode* root) {
        if(!root) return 0;
        int left = dfs(root->left);
        int right = dfs(root->right);
        res += abs(left) + abs(right);
        return root->val - 1 + left + right;
    }
public:
    int distributeCoins(TreeNode* root) {
        dfs(root);
        return res;
    }
};


