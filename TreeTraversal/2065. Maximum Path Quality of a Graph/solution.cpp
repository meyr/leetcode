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
