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
