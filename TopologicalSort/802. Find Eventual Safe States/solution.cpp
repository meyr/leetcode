/*
 *
 *  time  : O(NM + N + NM + KlogK) = O(NM + KlogK)
 *  space : O(N + NM) = O(NM)
 */
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int sz = graph.size();
        vector<int> ind(sz);
        unordered_map<int, vector<int>> m;
        for(int i = 0; i < sz; ++i) {  // O(NM)
            for(auto& e : graph[i]) {
                m[e].push_back(i); // i-->e
                ind[i]++;
            }
        }
        queue<int> q;
        vector<int> ans;
        for(int i = 0; i < sz; ++i) {   // O(N)
            if(ind[i] == 0) q.push(i);
        }
        while(!q.empty()) {             // O(NM)
            int n = q.front(); q.pop();
            ans.push_back(n);
            for(auto& prev : m[n]) {
                if(--ind[prev] == 0)
                    q.push(prev);
            }
        }
        sort(begin(ans), end(ans));     // O(KlogK)
        return ans;
    }
};
