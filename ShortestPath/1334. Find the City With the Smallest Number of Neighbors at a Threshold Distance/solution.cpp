/*
 * 使用floyd-washer找出每個node到其他點的最短距離
 *
 * time  : O(N^3)
 * space : O(N^2)
 */

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dist(n, vector<int>(n, 1e8));
        for(auto& e : edges) {
            dist[e[0]][e[1]] = min(dist[e[0]][e[1]], e[2]);
            dist[e[1]][e[0]] = min(dist[e[1]][e[0]], e[2]);
        }
            
        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    if(i != k && j != k && i != j && dist[i][k] + dist[k][j] <= distanceThreshold)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        
        int cnt{n + 1}, idx = -1;
        for(int i = 0; i < n; ++i) {
            int c{};
            for(int j = 0; j < n; ++j)
                c += dist[i][j] <= distanceThreshold;
            if(c <= cnt) {
                idx = i;
                cnt = c;
            }
        }
        return idx;
    }
};
