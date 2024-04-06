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
