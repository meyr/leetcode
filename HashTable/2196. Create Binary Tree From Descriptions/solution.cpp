/*
 *  因為數字都是unique所以使用unordered_map來記錄
 *  最後再根據c2p來找出root
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> v2n; // value to node
        unordered_map<int, int> c2p; // child to parent
        for(auto& d : descriptions) {
            int p = d[0], c = d[1], isLeft = d[2];
            if(!v2n.count(p)) v2n[p] = new TreeNode(p);
            if(!v2n.count(c)) v2n[c] = new TreeNode(c);
            if(isLeft) v2n[p]->left = v2n[c];
            else v2n[p]->right = v2n[c];
            c2p[c] = p;
        }
        int c = descriptions.front()[1];
        while(c2p.count(c))
            c = c2p[c];
        return v2n[c];
    }
};
