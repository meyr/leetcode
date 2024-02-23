/*
	很直覺的使用BFS 但是必須注意更新vector<int> dist的時機

*/
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        unordered_map<int, vector<pair<int, int>>> m;
        for(auto& f : flights)
            m[f[0]].push_back({f[1], f[2]});
        queue<int> q{{src}};
        while(!q.empty() && k >= 0) {
            vector<int> tmp(dist); // 不直接update dist因為可能會再把其他node拿出來使用
								   // 或是queue改成queue<pair<int, int>>把dist存在裡面	
            for(int loop = q.size(); loop > 0; --loop) {
                int cur = q.front(); q.pop();
                for(auto& [nxt, d] : m[cur]) {
                    if(dist[cur] + d < tmp[nxt]) {
                        tmp[nxt] = dist[cur] + d;
                        q.push(nxt);
                    }
                }
            }
            k--;
            swap(dist, tmp);
        }
        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};
