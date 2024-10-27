/*
 *  標準的UnionFind題目
 *  不斷的連結edge直到有個edge已經是互通了
 *
 */
class Solution {
    vector<int> root, rank;
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    int un(vector<int>& v) {
        int a = v[0], b = v[1];
        a = find(a), b = find(b);
        if(a == b) return 0;
        if(rank[a] < rank[b]) swap(a, b);
        root[b] = a;
        return rank[a] += rank[b];
    }
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        root.resize(n + 1), rank.resize(n + 1, 1);
        iota(begin(root), end(root), 0);
        for(auto& e : edges) {
            if(!un(e)) return e;
        }
        return {};
    }
};
