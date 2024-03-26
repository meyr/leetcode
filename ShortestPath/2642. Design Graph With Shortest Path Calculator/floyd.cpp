class Graph {
    int n;
    vector<vector<long>> dist;
    bool dirty;
    void floyd() {
        for(int k = 0; k < n; ++k) {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < n; ++j) {
                    if(i == j) continue;
                    if(dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
public:
    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        dist.resize(n, vector<long>(n, INT_MAX));
        for(int i = 0; i < n; ++i) dist[i][i] = 0;
        for(auto& e : edges)
            dist[e[0]][e[1]] = e[2];
        dirty = true;
    }
    
    void addEdge(vector<int> edge) {
        if(dist[edge[0]][edge[1]] > edge[2]) {
            dist[edge[0]][edge[1]] = edge[2];
            dirty = true;
        }
    }
    
    int shortestPath(int node1, int node2) {
        if(dirty) {
            floyd();
            dirty = false;
        }
        if(dist[node1][node2] >= INT_MAX) return -1;
        else return dist[node1][node2];
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */
