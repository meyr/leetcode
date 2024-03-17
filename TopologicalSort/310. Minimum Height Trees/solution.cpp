/*
 *   標準的topological sort問題 
 *   但是必須記錄每個過程即是ans
 *
 *   time  : O(E + N)
 *   space : O(N + E)
 */

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n == 1) return {0};
        vector<int> ind(n);
        unordered_map<int, vector<int>> adj;
        for(auto& e : edges) { // O(E)
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
            ind[e[0]]++;
            ind[e[1]]++;
        }
        queue<int> q;
        vector<int> ans;
        for(int i = 0; i < n; ++i)
            if(ind[i] == 1) q.push(i);
        while(!q.empty()) { // O(N) 每個node都會走訪過一次
            ans = move(vector<int>());
            for(int loop = q.size(); loop > 0; --loop) {
                int p = q.front(); q.pop();
                ans.push_back(p);
                for(auto& nxt : adj[p]) {
                    if(--ind[nxt] == 1) q.push(nxt);
                }
            }
        }
        return ans;
    }
};
