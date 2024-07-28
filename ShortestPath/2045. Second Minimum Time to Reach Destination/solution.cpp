/*
 * 參考: https://leetcode.com/problems/second-minimum-time-to-reach-destination/solutions/5546126/easy-c-solution-with-video-explanation/
 *
 * 一般的dijstra使用vector<int> dist;來紀錄最小的距離。因為我們要知道second minimum time所以
 * 使用vector<priority_queue<int>> dist; 來紀錄最小和第二小的距離。
 *
 */
class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        unordered_map<int, vector<int>> adj;
        for(auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        vector<priority_queue<int>> dist(n + 1, priority_queue<int>());// __important__ 使用vector<priority_queue>> 來紀錄最小和第二小距離
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // time, node
        pq.push(make_pair(0, 1));
        while(!pq.empty()) {
            auto [t, cur] = pq.top(); pq.pop();
            if((t / change) % 2 == 1)
                t += change - (t % change);
            t += time;
            for(auto& nxt : adj[cur]) {
                if(dist[nxt].size() == 0) {// 沒訪問過
                    dist[nxt].push(t);
                    pq.push(make_pair(t, nxt));
                } else if(dist[nxt].size() == 1 && dist[nxt].top() != t) {// 有訪問過一次
                    dist[nxt].push(t);
                    pq.push(make_pair(t, nxt));
                } else if(dist[nxt].top() > t) {// 訪問超過兩次，如果distance > dist[it].top() 也就是有可能是second minimum或是minimum
                    dist[nxt].pop();            // 則把最大的丟掉，把目前的值放進去。
                    dist[nxt].push(t);
                    pq.push(make_pair(t, nxt));
                }
            }
        }
        return dist.back().top();
    }
};
