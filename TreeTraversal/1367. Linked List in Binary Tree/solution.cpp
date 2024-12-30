/*
 *  time  : O(NM) , N : size of TreeNode, M : size of ListNode
 *  space : O(NM)
 */
class Solution {
    ListNode* _head;
    bool check(TreeNode* root, ListNode* head) {
        if(!head) return true;
        else if(!root) return false;
        else if(root->val != head->val) return false;
        else return check(root->left, head->next) || check(root->right, head->next);        
    }
    bool dfs(TreeNode* root) {
        if(!root) return false;
        bool rtn{false};
        if(root->val == _head->val) rtn |= check(root, _head);
        if(rtn) return rtn;
        rtn |= dfs(root->left) || dfs(root->right);
        return rtn;
    }
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        _head = head;
        return dfs(root);
    }
};
