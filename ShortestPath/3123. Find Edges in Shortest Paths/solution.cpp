/*
 *   參考解答 : https://leetcode.com/problems/find-edges-in-shortest-paths/solutions/5052500/dijkstra-backtracking/
 *
 *   用dijistra可以找到從node 0 到 node 1 ~ n-1的最短距離
 *   問題是怎麼找出最短距離的路徑
 *
 *   這邊是使用相同的min heap 因為已經有最短路徑了
 *   所以走回去符合數值的即是路徑上
 */

class Solution {
    template<typename T>
    using minhp = priority_queue<T, vector<T>, greater<>>;
public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        int sz = edges.size();
        vector<bool> res(sz, false);
        unordered_map<int, vector<vector<int>>> adj; // from, <to, weight, index>
        for(int i = 0; i < edges.size(); ++i) {
            vector<int>& e = edges[i];
            adj[e[0]].push_back({e[1], e[2], i});
            adj[e[1]].push_back({e[0], e[2], i});
        }
        minhp<pair<int, int>> pq; // weight, node
        vector<int> path(n, INT_MAX); // __important__ 從node 0到node 1 ~ n - 1的最短路徑
        pq.push(make_pair(0, 0));
        path[0] = 0;
        while(!pq.empty()) {
            auto [w, n] = pq.top(); pq.pop();
            if(w <= path[n]) { // __important__ 如果weight小於等於目前node n的最短距離 才需要繼續檢查
                for(auto& nxt : adj[n]) {
                    int to = nxt[0], weight = nxt[1];
                    if(w + weight < path[to]) {
                        path[to] = w + weight;
                        pq.push(make_pair(path[to], to));
                    }
                }
            }
        }
        pq.push(make_pair(path[n - 1], n - 1));  // 找到目前node 0到 node n-1 的最短距離
        while(!pq.empty()) {
            auto [w, n] = pq.top(); pq.pop();
            for(auto& nxt : adj[n]) {
                int to = nxt[0], weight = nxt[1], idx = nxt[2];
                if(w - weight == path[to]) { // 表示這條路徑在最短路徑上
                    res[idx] = true;
                    pq.push(make_pair(path[to], to));
                }
            }
        }
        return res;
    }
};
