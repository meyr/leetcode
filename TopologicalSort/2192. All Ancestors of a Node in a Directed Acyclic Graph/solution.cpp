/*
 *  很直覺的使用topological sort，
 *  並且每次都把目前的node和身上所有的node往下一個地方推
 *
 *  但是答案要求需要排序和unique
 *  所以使用以下 
 *
 *  sort(begin(vec), end(vec));
 *  vec.erase(unique(begin(vec), end(vec)), vec.end());
 *
 */

class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int>> ans(n, vector<int>());
        unordered_map<int, vector<int>> adj;
        vector<int> ind(n);
        for(auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            ind[e[1]]++;
        }
        queue<int> q;
        for(int i = 0; i < n; ++i)
            if(ind[i] == 0) q.push(i);
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(auto& nxt : adj[cur]) {
                ans[nxt].push_back(cur);
                for(auto& n : ans[cur]) ans[nxt].push_back(n);
                if(--ind[nxt] == 0) {
                    q.push(nxt);
                    sort(begin(ans[nxt]), end(ans[nxt]));
                    ans[nxt].erase( unique( ans[nxt].begin(), ans[nxt].end() ), ans[nxt].end() );
                }
            }
        }
        return ans;
    }
};
