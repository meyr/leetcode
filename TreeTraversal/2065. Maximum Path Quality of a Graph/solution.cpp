/*
 * 參考 : https://leetcode.com/problems/maximum-path-quality-of-a-graph/solutions/1563744/plain-dfs/
 *
 * 一開始也是想到用DFS來解 因為沒什麼特別的想法 所以就是暴力破解 只要走道node0就紀錄目前的value
 * 但是遇到一個問題是怎麼統計經過的node 後來參考解答使用vector<int> visited; 經過就+1退回就-1
 * 這樣就可以知道什麼時候需要加減value
 *
 */

class Solution {
    unordered_map<int, unordered_map<int, int>> adj;
    int ans{};
    void helper(vector<int>& values, vector<int>& visited, int cur, int times, int val) {
        if(visited[cur]++ == 0) val += values[cur]; // 第一次訪問才須要增加value
        if(cur == 0) ans = max(ans, val); // 回到node0時表示是valid path紀錄目前的最大value
        for(auto& nxt : adj[cur])
            if(nxt.second <= times)
                helper(values, visited, nxt.first, times - nxt.second, val);
        if(visited[cur]-- == 1) val -= values[cur]; // 最後一次被退回才需要減掉value
    }
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        for(auto& e : edges) {
            adj[e[0]][e[1]] = e[2];
            adj[e[1]][e[0]] = e[2];
        }
        int sz = values.size();
        vector<int> visited(sz); // count how many times we visited the node
        helper(values, visited, 0, maxTime, 0);
        return ans;
    }
};
/*  2025/12/23 再寫一次還是MLE
 *  主要是傳遞unordered_set<int>來統計訪問過的node太浪費記憶體
 *  如果要修改成使用vector<int> visited就必須使用dfs不能使用bfs
 *  類似recursive一樣訪問過就+1, 回去就-1 這樣才可以節省memory
 */
class Solution {
    using state = pair<vector<int>, unordered_set<int>>;
    unordered_map<int, vector<vector<int>>> adj;
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        for(auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
        queue<state> q;
        int ans{};
        q.push({
            {0, maxTime, 0},    // cur node, remain time, quality
            {}                  // visited node
        });
        while(!q.empty()) {
            auto [st, vis] = q.front(); q.pop();
            int cur = st[0], time = st[1], qty = st[2];
            //if(time < 0) continue;
            if(!vis.count(cur))
                qty += values[cur];
            vis.insert(cur);
            if(cur == 0) ans = max(ans, qty);
            for(auto& nxt : adj[cur]) {
                if(nxt[1] <= time) {
                    q.push({
                        {nxt[0], time - nxt[1], qty},
                        vis
                    });
                }
            }
        }
        return ans;
    }
};
/*  根據上面的解答改成DFS
 *
 */
class Solution {
    int ans{};
    unordered_map<int, vector<vector<int>>> adj;
    void helper(int cur, vector<int>& visited, vector<int>& values, int time, int qty) {
        qty += visited[cur] == 0 ? values[cur] : 0;
        visited[cur]++;
        if(cur == 0)
            ans = max(ans, qty);
        for(auto& nxt : adj[cur]) {
            if(nxt[1] <= time)
                helper(nxt[0], visited, values, time - nxt[1], qty);
        }
        visited[cur]--;
    }
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int sz = values.size();
        for(auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
        vector<int> visited(sz);
        helper(0, visited, values, maxTime, 0);
        return ans;
    }
};
