/*  這題想了一陣子 如果是面試可能就超時了
 *
 *  首先先思考如果沒有bob的情況, 那就是BFS解法, 直到遇到leaf node, 並且使用ans來記錄最大值
 *  問題來了, 如果有bob且bob一定會朝node 0前進, 所以bob的路徑是固定的, 我們在乎的是bob的路徑和經過每個node的時間
 *
 *  怎麼找出bob到達node 0的路徑和時間? 我這邊使用DFS, 當到達node 0就返回true並且記錄經過的時間
 *
 *  有了vector<int> bt; // time bob reach each node
 *  就可以繼續使用BFS
 *
 *
 */
class Solution {
    unordered_map<int, vector<int>> m;
    unordered_set<int> leaves;
    vector<int> bt, score;
    int sz;
    bool dfs(int cur, int par, int time) {  // 紀錄bob朝node 0前進的每個node時間
        if(cur == 0) {
            bt[cur] = time;
            return true;
        }
        for(auto& nxt : m[cur]) {
            if(nxt == par) continue;
            if(dfs(nxt, cur, time + 1)) {
                bt[cur] = time;
                return true;
            }
        }
        return false;
    }
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        sz = edges.size() + 1;
        vector<int> ind(sz);
        for(auto& edge : edges) {               
            m[edge[0]].push_back(edge[1]);
            m[edge[1]].push_back(edge[0]);
            ind[edge[0]]++;
            ind[edge[1]]++;
        }
        for(int i = 1; i < sz; ++i)             // 找出leaf node 但是跳過node 0
            if(ind[i] == 1) leaves.insert(i);
        bt.resize(sz, INT_MAX);
        score.resize(sz);
        dfs(bob, -1, 1);
        int ans{INT_MIN}, time = 1;
        queue<pair<int, int>> q; // node, parent
        q.push({0, -1});
        while(!q.empty()) {
            for(int loop = q.size(); loop > 0; --loop) {
                auto [cur, par] = q.front(); q.pop();
                int sc = par > -1 ? score[par] : 0;             
                if(bt[cur] == time) sc += amount[cur] / 2;
                else if(bt[cur] > time) sc += amount[cur];
                score[cur] = sc;
                if(leaves.count(cur)) {
                    ans = max(ans, score[cur]);
                    continue;
                }
                for(auto& nxt : m[cur]) {
                    if(nxt == par) continue;
                    q.push({nxt, cur});
                }
            }
            time++;
        }
        return ans;
    }
};
/* 參考解答 : 
 * https://leetcode.com/problems/most-profitable-path-in-a-tree/solutions/2807150/2-dfs-1-dfs-simple-approach-c-by-brehamp-mcmp/
 * 
 * 使用depth來記錄alice從node0開始走多少距離了
 * 使用distFromBob來記錄從node bob走上來多少距離了
 */
class Solution {
public:
    vector<vector<int>>adj;
    vector<int>disFromBob;
    int bobNode;
    // dfs先呼叫dfs更新了distFromBob, 所以回來的時候distFromBob已全部更新完畢
    int dfs(int cur,int par,int depth,vector<int>&amount){
        int ret = 0;
        if(cur == bobNode) disFromBob[cur] = 0;
        else disFromBob[cur] = amount.size();
        int maxChild = -INT_MAX;
        for(int nxt : adj[cur]){
            if(nxt == par)continue;
            maxChild = max(maxChild, dfs(nxt, cur, depth + 1, amount)); // __important__ 先往下找，要計算distFromBob[cur] 必須先知道distFromBob[nxt]所以先呼叫dfs
                                                                        //               選一個到達leave之後最大的child路徑
            disFromBob[cur] = min(disFromBob[cur], disFromBob[nxt] + 1); // 更新從bobNode到此node的距離
        }
        // 計算此node的分數
        if(disFromBob[cur] > depth) ret += amount[cur];             // 比bob先到
        else if(disFromBob[cur] == depth) ret += amount[cur]/2;     // 同時到達

        // 返回此node和最大child的數值
        if(maxChild == -INT_MAX) return ret;                        // 沒有child 直接回傳此node的值
        else return ret + maxChild;                                 
    }
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int n = amount.size();
        bobNode = bob;
        adj.resize(n,vector<int>());
        for(auto&e:edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        disFromBob.resize(n);
        return dfs(0, 0, 0, amount);
    }

};
