/*  
 *  參考解答 https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/solutions/1097180/c-djikstra-and-dfs/
 * 
 *  1. 先找出每個node x 到 node n的最短距離 使用Dijkstra演算法
 *  2. 使用dfs來計算通往node n的方法 因為使用dfs可以用memorize來加速 
 */

class Solution {
    vector<int> dist, dp;
    unordered_map<int, vector<pair<int, int>>> adj; // from, to, weight
    int mod = 1e9 + 7;
    int helper(int cur) {
        if(~dp[cur]) return dp[cur];
        int sum{}; // 達到此node的方法數
        for(auto& [next, wt] : adj[cur]) {
            if(dist[cur] > dist[next]) // 滿足restricted path的條件
                sum = (sum + helper(next)) % mod;
        }
        return dp[cur] = sum;
    }
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        for(auto& e : edges) {
            adj[e[0]].push_back(make_pair(e[1], e[2]));
            adj[e[1]].push_back(make_pair(e[0], e[2]));
        }
        dist.resize(n + 1, INT_MAX);
        dist[n] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // minheap, <dist, node>
        pq.push(make_pair(0, n));
        while(!pq.empty()) {
            auto [d, p] = pq.top(); pq.pop();
            for(auto& [next, wt] : adj[p]) {
                if(dist[next] > dist[p] + wt) {
                    dist[next] = dist[p] + wt;
                    pq.push(make_pair(dist[next], next));
                }
            }
        }
        dp.resize(n + 1, -1);
        dp[n] = 1;
        return helper(1);
    }
};
