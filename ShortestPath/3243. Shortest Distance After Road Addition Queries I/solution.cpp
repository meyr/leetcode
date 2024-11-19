/*
 *  標準的最短路徑問題
 *  
 *  先把預設路徑建立起來 i->i+1 (i < n - 1)
 *  每次query就把新的路徑加進來
 */
class Solution {
    unordered_map<int, vector<int>> path;
    int helper(int n) {
        queue<int> q{{0}};
        vector<int> dist(n, INT_MAX);
        dist[0] = 0;
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(auto& nxt : path[cur]) {
                if(dist[nxt] > dist[cur] + 1) {
                    dist[nxt] = dist[cur] + 1;
                    q.push(nxt);
                }
            }
        }
        return dist.back();
    }
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        for(int i = 1; i < n; ++i) path[i - 1].push_back(i);
        vector<int> ans;
        for(auto& q : queries) {
            path[q[0]].push_back(q[1]);
            ans.push_back(helper(n));
        }
        return ans;
    }
};
/*  改進效率 : 其實不用每次都從node 0開始 只要從更新node開始就可以
 *
 */
class Solution {
    queue<int> q;
    unordered_map<int, vector<int>> path;
    vector<int> dist;
    void helper() {
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(auto& nxt : path[cur]) {
                if(dist[nxt] > dist[cur] + 1) {
                    dist[nxt] = dist[cur] + 1;
                    q.push(nxt);
                }
            }
        }
    }
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        dist.resize(n);
        iota(begin(dist), end(dist), 0);
        for(int i = 1; i < n; ++i) path[i - 1].push_back(i);
        vector<int> ans;
        for(auto& qry : queries) {
            path[qry[0]].push_back(qry[1]);
            q.push(qry[0]);
            helper();
            ans.push_back(dist.back());
        }
        return ans;
    }
};
