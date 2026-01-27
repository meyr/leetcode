/*  一開始這樣寫結果錯了
 *  因為這樣只考慮從n-1過來反向的路徑 沒考慮到中間反向路徑
 */
class Solution {
    int n;
    unordered_map<int, vector<pair<int, int>>> adj;
    vector<int> helper(int st) {
        vector<int> dist(n, INT_MAX);
        dist[st] = 0;
        queue<int> q{{st}};
        while(!q.empty()) {
            auto cur = q.front(); q.pop();
            for(auto& [nxt, w] : adj[cur]) {
                if(dist[nxt] > dist[cur] + w) {
                    dist[nxt] = dist[cur] + w;
                    q.push(nxt);
                }
            }
        }
        return dist;
    }
public:
    int minCost(int n, vector<vector<int>>& edges) {
        for(auto& e : edges)
            adj[e[0]].push_back({e[1], e[2]});
        this->n = n;
        vector<int> dist0 = helper(0);
        vector<int> distn = helper(n - 1);
        int ans{INT_MAX};
        for(int i = 0; i < n; ++i)
            ans = min(ans, dist0[i] + 2 * distn[i]);
        return ans >= INT_MAX ? -1 : ans;
    }
};
/*  因為每個node只能反向一次 所以使用dist[n][2]來記錄有沒有反向的最短路徑
 *  但是執行效率不好
 */
class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        unordered_map<int, vector<vector<int>>> adj;
        for(auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2], 0});
            adj[e[1]].push_back({e[0], 2 * e[2], 1});
        }
        vector<vector<int>> dist(n, vector<int>(2, INT_MAX));
        dist[0][0] = 0;
        queue<int> q{{0}};
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(auto& next : adj[cur]) {
                int nxt = next[0], w = next[1], idx = next[2];
                if(dist[nxt][idx] > min(dist[cur][0], dist[cur][1]) + w) {  //__importatn__ dist[nxt][idx] 是由前一個node不管有沒有反向 最短路徑 + w決定
                    dist[nxt][idx] = min(dist[cur][0], dist[cur][1]) + w;
                    q.push(nxt);
                }
            }
        }
        int ans = min(dist.back()[0], dist.back()[1]);
        return ans == INT_MAX ? -1 : ans;
    }
};
/*  參考解答 使用dijkstra效率比較好
 *
 */
class Solution {
    template<typename T>
    using minheap = priority_queue<T, vector<T>, greater<>>;
public:
    int minCost(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> adj(n);
        for(auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], 2 * e[2]});
        }
        minheap<pair<int, int>> pq;
        vector<int> dist(n, INT_MAX);
        dist[0] = 0;
        pq.push({0, 0});
        while(!pq.empty()) {
            auto [cw, cur] = pq.top(); pq.pop();
            if(cur == n - 1) return cw;
            if(cw > dist[cur]) continue;
            for(auto& [nxt, w] : adj[cur]) {
                if(dist[nxt] > dist[cur] + w) {
                    dist[nxt] = dist[cur] + w;
                    pq.push({dist[nxt], nxt});
                }
            }
        }
        return -1;
    }
};
