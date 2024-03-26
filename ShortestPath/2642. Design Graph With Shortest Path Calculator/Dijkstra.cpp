class Graph {
    int n;
    unordered_map<int, vector<pair<int, int>>> adj;
public:
    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        for(auto& e : edges)
            adj[e[0]].push_back(make_pair(e[1], e[2]));
    }
    
    void addEdge(vector<int> edge) {
        adj[edge[0]].push_back(make_pair(edge[1], edge[2]));
    }
    
    int shortestPath(int node1, int node2) {
        priority_queue<pair<long, int>, vector<pair<long, int>>, greater<>> pq;//minheap, dist, node
        vector<long> dist(n, INT_MAX); // 從node1到任一node的距離
        dist[node1] = 0;
        pq.push(make_pair(0, node1));
        while(!pq.empty()) {
            auto [d, cur] = pq.top(); pq.pop();
            for(auto& nxt : adj[cur]) {
                if(dist[nxt.first] > d + nxt.second) {
                    dist[nxt.first] = d + nxt.second;
                    pq.push(make_pair(dist[nxt.first], nxt.first));
                }
            }
        }
        return dist[node2] >= INT_MAX ? -1 : dist[node2];
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */
