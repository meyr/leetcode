/*
 *  另一種最短路徑解法 dijkstra
 *
 */
class Solution {
    int sz, dt;
    vector<vector<pair<int, int>>> adj;
    template<typename T>
    using minhp = priority_queue<T, vector<T>, greater<>>;
    int check(int node) {
        vector<int> dist(sz, 1e8);
        minhp<pair<int, int>> pq; // dist, node
        pq.push(make_pair(0, node));
        dist[node] = 0;
        while(!pq.empty()) {
            auto [d, p] = pq.top(); pq.pop();
            if(d == dist[p]) {
                for(auto& [nd, nn] : adj[p]) {
                    if(d + nd < dist[nn] && d + nd <= dt) {
                        dist[nn] = d + nd;
                        pq.push(make_pair(dist[nn], nn));
                    }
                }
            }
        }
        int rtn{};
        for(int i = 0; i < sz; ++i) {
            if(i == node) continue;
            rtn += dist[i] <= dt;
        }
        return rtn;
    }
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        this->sz = n;
        this->dt = distanceThreshold;
        adj.resize(sz, vector<pair<int, int>>());
        for(auto& e : edges) {
            adj[e[0]].push_back(make_pair(e[2], e[1]));
            adj[e[1]].push_back(make_pair(e[2], e[0]));
        }
        int ans{sz + 1}, idx = -1;
        for(int i = 0; i < sz; ++i) {
            int rtn = check(i);
            if(rtn <= ans) {
                ans = rtn;
                idx = i;
            }
        }
        return idx;
    }
};
