class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> ans;
        if(!root) return ans;
        queue<Node*> q{{root}};
        while(!q.empty()) {
            vector<int> tmp;
            for(int i = q.size(); i > 0; --i) {
                Node* p = q.front(); q.pop();
                tmp.push_back(p->val);
                for(Node* c : p->children) q.push(c);
            }
            ans.push_back(tmp);
        }
        return ans;
	// time : O(N)
	// space : O(N)
    }
};
