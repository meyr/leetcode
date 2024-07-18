/*  使用dijistra找出最短路徑，並且注意disappear的時間，超過就不處理
 *  同時ans[node]也是身兼是否訪問過的意思。
 *
 *  time  : O(E + N)
 *  space : O(E + N) 
 */
class Solution {
    unordered_map<int, vector<pair<int, int>>> adj;
    template<typename T>
    using minhp = priority_queue<T, vector<T>, greater<>>;    
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        for(auto& e : edges) {
            adj[e[0]].push_back(make_pair(e[1], e[2])); // from, <to, time>
            adj[e[1]].push_back(make_pair(e[0], e[2]));
        }
        vector<int> ans(n, -1);
        minhp<pair<int, int>> q; // time, node
        q.push(make_pair(0, 0));
        while(!q.empty()) {
            auto [time, node] = q.top(); q.pop();
            if(disappear[node] > time && ans[node] == -1) {
                ans[node] = time;
                for(auto& [nxt, t] : adj[node]) {
                    if(ans[nxt] == -1)
                        q.push(make_pair(time + t, nxt));
                }
            }
        }
        return ans;
    }
};
/*  2024/07/18
 *  一開始的想法是用BFS 結果TLE
 *
 *  因為有可能一開始的路徑很長        a--100000->... -->b--100000-->c
 *  但是有一條路徑較短                a--1-->d--1-->e--1-->f--1-->g--1-->h ... --1-->c
 *  如果使用一般的queue
 *  需要每條都走看看 花比較多時間
 */
class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());
        for(auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
        vector<int> rtn(n, INT_MAX);
        rtn[0] = 0;
        queue<pair<int, int>> q;
        q.push({0, 0});
        while(!q.empty()) {
            auto [n, t] = q.front(); q.pop();
            for(auto& nxt : adj[n]) {
                int nxttime = t + nxt.second;
                int nxtnode = nxt.first;
                if(nxttime < disappear[nxtnode] && nxttime < rtn[nxtnode]) {
                    rtn[nxtnode] = nxttime;
                    q.push({nxtnode, nxttime});
                }
            }
        }
        for(int i = 1; i < n; ++i)
            if(rtn[i] == INT_MAX) rtn[i] = -1;
        return rtn;
    }
};
/*
 *  參考解答 : https://leetcode.cn/problems/minimum-time-to-visit-disappearing-nodes/solutions/2844219/fang-wen-xiao-shi-jie-dian-de-zui-shao-s-w9sv/
 *  因為是"最短路徑" 所以使用minheap是不是比較有效率
 *  先處理時間最短的node 之後這個node視為最短路徑了 不需要再處理
 *  __所以判斷從pq拿出來的node是否是最短時間__
 */

class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());
        for(auto& e : edges) {
            adj[e[0]].push_back(make_pair(e[2], e[1]));
            adj[e[1]].push_back(make_pair(e[2], e[0]));
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push(make_pair(0, 0));
        vector<int> rtn(n, -1);
        rtn[0] = 0;
        while(!pq.empty()) {
            auto [cur, node] = pq.top(); pq.pop();
            if(rtn[node] != cur) continue; // ** important 必須先判斷此node是否是最短時間 不然不用再跑下去
            for(auto& [len, nxt] : adj[node]) {
                if(cur + len < disappear[nxt] && (rtn[nxt] == -1 || rtn[nxt] > cur + len)) {
                    rtn[nxt] = cur + len;
                    pq.push(make_pair(rtn[nxt], nxt));
                }
            }
        }
        return rtn;
    }
};


