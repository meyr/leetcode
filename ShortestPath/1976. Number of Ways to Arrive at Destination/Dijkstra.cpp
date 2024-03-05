/*  
 * 參考解答 https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/solutions/1417576/c-python-dijkstra-clean-concise/
 *
 * 使用minheap 每次都從最短路徑出發 一路更新從source到任一點的最短距離
 * 使用dijkstra的缺點是 只會針對某個node出發到graph任一點
 * 
 * 使用minheap的理由是 目前最短路徑有可能也是下一個node的最短路徑
 */

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        int mod = 1e9 + 7;
        vector<vector<pair<long long, long long>>> graph(n);
        for(auto& r : roads) {
            graph[r[0]].push_back(make_pair(r[1], r[2]));
            graph[r[1]].push_back(make_pair(r[0], r[2]));
        }
        vector<long long> dist(n, LONG_MAX); // the distance from 0 to x
        vector<long long> ways(n);           // the ways from 0 to x
        ways[0] = 1, dist[0] = 0;
        priority_queue<pair<long, long>, vector<pair<long, long>>, greater<>> pq;//minheap
        pq.push(make_pair(0, 0)); // dist, source
        while(!pq.empty()) {
            auto [d, cur] = pq.top(); pq.pop();
            if(d > dist[cur]) continue;
            for(auto [nxt, time] : graph[cur]) {
                if(d + time < dist[nxt]) { 
                    dist[nxt] = d + time;
                    ways[nxt] = ways[cur];
                    pq.push(make_pair(dist[nxt], nxt));
                } else if(dist[nxt] == d + time)
                    ways[nxt] = (ways[nxt] + ways[cur]) % mod;
            }
        }
        return ways[n - 1];
    }
};
