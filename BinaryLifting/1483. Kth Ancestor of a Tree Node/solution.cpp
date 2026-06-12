/*
 *  參考binary lifting的筆記
 *  https://hackmd.io/iP9jJAIzSj-38UJPDM4xmA
 *
 *  time  : O(32N) = O(N) 建立table, O(1) 查詢
 *  space : O(32N) = O(N) table size
 */

class TreeAncestor {
    vector<vector<int>> p;
public:
    TreeAncestor(int n, vector<int>& parent) {
        p.push_back(parent);
        for(int i = 1; i < 31; ++i) {
            vector<int> tmp(n, -1);
            for(int j = 0; j < n; ++j) {
                if(p[i - 1][j] != -1) {
                    tmp[j] = p[i - 1][p[i - 1][j]];
                }
            }
            p.push_back(tmp);
        }
    }
    
    int getKthAncestor(int node, int k) {
        for(int i = 31; i >= 0; --i) {
            if((k >> i) & 1) {
                if(p[i][node] == -1) return -1;
                else node = p[i][node];
            }
        }
        return node;

    }
};
/*  閱讀完 3559. Number of Ways to Assign Edge Weights II 後重新寫一次
 *  建立parent table parent[cur][j] 其中j為向上2^j個node
 *
 */
class TreeAncestor {
    vector<vector<int>> parent;
    vector<vector<int>> adj;
    int log_max;
    void dfs(int cur, int par) {
        parent[cur][0] = par;
        for(int j = 1; j < log_max; ++j)
            if(parent[cur][j - 1] != -1)
                parent[cur][j] = parent[parent[cur][j - 1]][j - 1];
        for(auto& nxt : adj[cur])
            if(nxt != par)
                dfs(nxt, cur);
    }
public:
    TreeAncestor(int n, vector<int>& p) {
        log_max = log2(n) + 1;
        parent.resize(n, vector<int>(log_max, -1));
        adj.resize(n);
        int r;
        for(int i = 0; i < n; ++i) {
            if(p[i] == -1) r = i;
            else adj[p[i]].push_back(i);
        }
        dfs(r, -1);

    }

    int getKthAncestor(int node, int k) {
        for(int j = log_max - 1; j >= 0; --j) {
            if((k >> j) & 1)
                node = parent[node][j];
            if(node == -1) return node;
        }
        return node;
    }
};
