/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        vector<long long> ans;
        queue<TreeNode*> q{{root}};
        while(!q.empty()) {
            long long sum{};
            for(int loop = q.size(); loop > 0; --loop) {
                TreeNode* p = q.front(); q.pop();
                sum += p->val;
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
            ans.push_back(sum);
        }
        if(k > ans.size()) return -1;
        sort(begin(ans), end(ans));		// 可以使用minheap取代
        return ans[ans.size() - k];
    }
};
