/*  ref : https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/solutions/1844095/three-dijkstras-by-votrubac-f7cc/
 *        https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/solutions/1844091/c-dijkstra-3-times-with-illustration-by-gonzf/
 *
 *  如果只考慮 scr --> dest 最短距離 可以使用dijkstra來解答
 *  現在有兩個scr1, scr2到達dest的路徑可能不一樣
 *
 *  但是會有一個中間點 x 使得 scr1-->x ---> dest  
 *                                  /|\
 *                            scr2---|
 *
 *  中間點可能是scr1, scr2或是 dest
 *      scr1的意思是scr2到dest會經過scr1
 *      scr2的意思是scr1到dest會經過scr2
 *      dest的意思是scr1和scr2沒有交集 只有終點才會交集在一起
 *      
 */
class Solution {
    template<typename T>
    using minheap = priority_queue<T, vector<T>, greater<>>;
    using path = unordered_map<int, vector<vector<int>>>;
    using ll = long long;

    path adj, radj;
    int sz;
    vector<ll> helper(path& p, int src) {
        vector<ll> rtn(sz, LLONG_MAX);
        rtn[src] = 0;
        minheap<pair<ll, int>> q;   // 使用minheap讓收斂比較快
        q.emplace(0, src);          
        while(!q.empty()) {
            auto [cost, cur] = q.top(); q.pop();
            if(cost > rtn[cur]) continue;   // 因為使用minheap這時判斷才有加速的效果
            for(auto& nxt : p[cur]) {
                if(rtn[nxt[0]] > rtn[cur] + nxt[1]) {
                    rtn[nxt[0]] = rtn[cur] + nxt[1];
                    q.push({rtn[nxt[0]], nxt[0]});
                }
            }
        }
        return rtn;
    }
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        sz = n;
        for(auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            radj[e[1]].push_back({e[0], e[2]});
        }
        auto dscr1 = helper(adj, src1);
        auto dscr2 = helper(adj, src2);
        auto ddest = helper(radj, dest);

        auto ans{LLONG_MAX};
        for(int i = 0; i < n; ++i) {
            if(dscr1[i] != LLONG_MAX && dscr2[i] != LLONG_MAX && ddest[i] != LLONG_MAX) { // 從scr1, scr2和dest都可以到達i
                auto total = dscr1[i] + dscr2[i] + ddest[i];
                ans = min(ans, total);
            }
        }
        return ans == LLONG_MAX ? -1 : ans;
    }
};
