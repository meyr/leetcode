/*
 *  參考 : https://leetcode.com/problems/modify-graph-edge-weights/solutions/3548231/dijkstra-algorithm-approach-beats-80-easy-to-understand/
 *
 */
class Solution {
public:
    vector<pair<int,int>> dp[200]; // 鄰近矩陣，在描述graph的路線
    vector<int> find(int n, int src, int dist) {
        vector<int> dis(n + 1, 1e9 + 10); // 預設路徑是不通
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>>pq; // minheap, <dist, node>
        pq.push({0, src});
        dis[src] = 0;
        vector<int> vis(n + 10,0);
        while(pq.size()) {
            auto [wt, node] = pq.top(); pq.pop();
            if(vis[node]) continue;
            vis[node]=1;
            for(auto &[current_node,current_wt] : dp[node]) {
                if(dis[current_node] > current_wt + wt) {
                    dis[current_node] = current_wt + wt;
                    pq.push({dis[current_node], current_node});
                }
            }
        }
        return dis;
    }

    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int src, int dest, int target) {
        for(auto &it:edges) {
            if(it[2] == -1) // 先把it[2] == -1視為不通
                continue;
            dp[it[0]].push_back({it[1],it[2]});
            dp[it[1]].push_back({it[0],it[2]});
        }
        vector<int> dist = find(n, src, dest);
        if(dist[dest] < target) {// 找到了比target還小的路徑，即使修改weight == -1也不會改變
            return {};
        } else if(dist[dest] == target) {// 如果剛好是target，把-1 edge全改成2e9(不通)
           for(auto &it : edges) {
               if(it[2] == -1)
                   it[2] = 2e9;
           }
           return edges;
       } else { // 比target還大的情況，只能嘗試連通weight = -1的路徑，看看是否會小於等於target
            for(int i = 0; i < edges.size(); i++) {
                int u = edges[i][0], v = edges[i][1], w = edges[i][2];
                if(w > 0) continue;
                    edges[i][2] = 1; // 連通這個路徑
                    dp[u].push_back({v,1});
                    dp[v].push_back({u,1});
                    vector<int> dis = find(n, src, dest); // 連通之後，試著根據現在狀況找出最小路徑
                    if(dis[dest] <= target) {// 這路徑有效，可以讓最短距離小於等於target
                        edges[i][2] += (target - dis[dest]); // 把剩下的都分配到這個edge
                        for(int j=i+1;j<edges.size();j++) { // 把其他的edge都設為最大，就是不相通
                            if(edges[j][2]==-1)
                                edges[j][2]=2e9;
                        }
                        return edges;
                    }
            }
       }
        return {};
    }
};
