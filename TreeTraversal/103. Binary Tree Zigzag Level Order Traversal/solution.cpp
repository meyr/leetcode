/*
	using level order traversal
	and reverse the vector if needed
*/

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
		// special case
        if(!root) return ans;	

        queue<TreeNode*> q{{root}};
        int level = 0;
        while(!q.empty()) {
            vector<int> tmp(q.size());
            for(int i = q.size(); i > 0; --i) {
                TreeNode* p = q.front(); q.pop();
                tmp.push_back(p->val);
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
            if(level % 2 == 1)
                reverse(begin(tmp), end(tmp));
            ans.push_back(tmp);
            level++;
        }
        return ans;
    }
};
