/* 
 *    因為是binary search tree所以使用in-order traversal就可以排序
 *    既然是排序過的vector，使用binary search來找出[min, max]
 */

class Solution {
    void helper(TreeNode* root, vector<int>& v) {
        if(!root) return;
        helper(root->left, v);
        v.push_back(root->val);
        helper(root->right, v);
    }
public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
       vector<int> v;
       helper(root, v); // O(N)
       vector<vector<int>> ans;
       for(auto& q : queries) { // O(NlogN)
           auto it = upper_bound(begin(v), end(v), q);
           if(it == v.begin()) ans.push_back({-1, *it});
           else if(q == *prev(it)) ans.push_back({q, q});
           else if(it == v.end()) ans.push_back({*prev(it), -1});
           else ans.push_back({*prev(it), *it});
       }
       return ans;
       // time : O(N + NlogN) = O(NlogN)
       // space : O(N + logN) = O(N)
    }
};
