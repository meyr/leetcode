/*  分別嘗試從red或是blue開始的node 0 依序走訪 並記錄最小距離
 *
 */
class Solution {
    enum COLOR{
        red,
        blue
    };
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<vector<int>> minDist(n, vector<int>(2, INT_MAX));
        minDist[0][red] = 0;
        minDist[0][blue] = 0;
        unordered_map<int, vector<int>> redadj, blueadj;
        for(auto& e : redEdges)
            redadj[e[0]].push_back(e[1]);
        for(auto& e : blueEdges)
            blueadj[e[0]].push_back(e[1]);
        queue<pair<int, int>> q;
        q.push({red, 0});
        q.push({blue, 0}); 
        while(!q.empty()) {
            auto [c, cur] = q.front(); q.pop();
            unordered_map<int, vector<int>>& adj = c == red ? redadj : blueadj;
            for(auto& nxt : adj[cur]) {
                if(minDist[nxt][c] > minDist[cur][!c] + 1) {
                    minDist[nxt][c] = minDist[cur][!c] + 1;
                    q.push({!c, nxt});
                }
            }
        }
        vector<int> rtn;
        for(int i = 0; i < n; ++i) {
            rtn.push_back(min(minDist[i][red], minDist[i][blue]));
            if(rtn.back() == INT_MAX)
                rtn.back() = -1;
        }
        return rtn;
    }
};
