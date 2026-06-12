/* 參考AI解答
 * 參考 : 3558. Number of Ways to Assign Edge Weights I
 *
 * 任兩點的組合就是 如果他們之間的長度len, 則答案是2^(len - 1)
 * 問題是怎麼有效率的找到任兩點之間的距離?
 *
 * distance(u, v) = depth(u) + depth(v) - 2 * depth(LCA(u, v))
 *
 * 所以問題變成如何建立每個node的depth和 如何快速查詢任兩點的LCA
 *
 * __important__ 查詢LCA的方法是 建立每個node的parent table 但考慮查詢和建立的效率 只建立2^j 個以上的parent
 *
 *               __init__
 *               parent[i][j] 就是表示node i往上2^j個node之後是誰
 *
 *               __create table__
 *
 *               int prev = parent[i][j - 1] 從i往上走 2^(j-1)
 *               parent[i][j] = parent[prev][j - 1]  要抵達2^j, 從prev往上走2^(j-1)
 *
 *               __query__
 *               我先往前跳最大的範圍2^j 如果parent一樣表示跳太多了 就少跳一點 j--
 *               直到找到 parent不一樣的點 那往上一個就是LCA
 *
 *               __addition__
 *               這種2的冪次的跳法也稱為 binary lifting 可以參考 1483. Kth Ancestor of a Tree Node
 *               一樣是建立parent table
 */
class Solution {
    vector<int> depth;
    vector<vector<int>> parent;
    vector<vector<int>> adj;
    int log_max;
    // c : current node
    // p : parent node
    // d : depth
    void dfs(int c, int p, int d) {
        depth[c] = d;
        parent[c][0] = p; // c往上一個是p
        for(int j = 1; j < log_max; ++j) {
            if(parent[c][j - 1] != -1) // 前2^(j - 1) 有parent的話
                parent[c][j] = parent[parent[c][j - 1]][j - 1];
            else break;
        }
        for(const auto& nxt : adj[c])
            if(nxt != p)
                dfs(nxt, c, d + 1);
    }
    void init(const vector<vector<int>>& edges) {
        for(const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        dfs(1, 0, 0);
    }
    int get_lca(int u, int v) {
        // 1. 先確保depth[u] >= depth[v]
        if(depth[u] < depth[v]) swap(u, v);
        // 2. 提升u的高度和v一樣
        int diff = depth[u] - depth[v];
        for(int j = 0; j < log_max; ++j)
            if((diff >> j) & 1)
                u = parent[u][j];
        if(u == v) return u;
        // 3. 兩個一起往上 從跳最大步的開始
        //    如果兩個parent一樣 表示跳太多了
        //            parent不一樣就往上跳
        for(int j = log_max - 1; j >= 0; --j) {
            if(parent[u][j] != parent[v][j]) {
                u = parent[u][j];
                v = parent[v][j];
            }
        }
        // 4. 再往上跳一個才是common ancestor
        return parent[u][0];
    }
    int powmod(int b, int e, int m = 1e9 + 7) {
        if(e == 0) return 1;
        else if(e == 1) return b;
        else {
            int val = powmod(b, e / 2, m);
            return (1LL * val * val * (e % 2 ? b : 1)) % m;
        }
    }
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int sz = edges.size() + 1;
        log_max = log2(sz) + 1;
        adj.resize(sz + 1);
        depth.resize(sz + 1);
        parent.resize(sz + 1, vector<int>(log_max, -1));

        init(edges);
        vector<int> rtn;
        for(const auto& q : queries) {
            int u = q[0], v = q[1];
            if(u == v) rtn.push_back(0);
            else {
                int lca = get_lca(u, v);
                int len = depth[u] + depth[v] - 2 * depth[lca];
                //cout << u << ", " << v << ", " << lca << ":" << depth[u] << ", " << depth[v] << ", " << depth[lca] << endl;
                rtn.push_back(powmod(2, len - 1));
            }
        }
        return rtn;
    }
};
