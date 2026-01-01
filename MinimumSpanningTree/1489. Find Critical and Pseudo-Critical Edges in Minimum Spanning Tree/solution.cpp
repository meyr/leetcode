class UnionFind{
    vector<int> root, rank;
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
public:
    UnionFind(int sz) : root(sz), rank(sz, 1) {
        iota(begin(root), end(root), 0);
    }
    int un(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return 0;
        if(rank[y] > rank[x]) swap(x, y);
        root[y] = x;
        return rank[x] += rank[y];
    }
};

class Solution {
    enum state{
        a, b, w, idx
    };
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int sz = edges.size();
        for(int i = 0; i < sz; ++i)
            edges[i].push_back(i);
        sort(begin(edges), end(edges), [](auto& a, auto& b){
            return a[w] < b[w];
        });

        // find minimum weights first
        int minWeights{};
        UnionFind uf(n);
        for(auto& e : edges) {
            int rtn = uf.un(e[a], e[b]);
            if(rtn) minWeights += e[w];
            if(rtn == n) break;
        }

        vector<vector<int>> ans(2, vector<int>());
        for(auto& cur : edges) {
            // check 1 不能有這個edge 
            UnionFind uf(n);
            int weights{}, rtn{};
            for(auto& e : edges) {
                if(e[idx] == cur[idx]) continue;
                rtn = uf.un(e[a], e[b]);
                if(rtn) weights += e[w];
                if(rtn == n) break;
            }

            // 發現如果移除edges[i]就組不成MST或是weights變大 --> 那就是critical path
            if(rtn < n || weights > minWeights) ans[0].push_back(cur[idx]);
            else {
                // check 2 一定要使用此edge
                UnionFind uf(n);
                uf.un(cur[a], cur[b]);
                int weights{cur[w]};
                int rtn{};
                for(auto& e : edges) {
                    if(e[idx] == cur[idx]) continue;
                    rtn = uf.un(e[a], e[b]);
                    if(rtn) weights += e[w];
                    if(rtn == n) break;
                }

                //也是可以組成MST --> 那就是pseudo-critical edges
                if(rtn == n && weights == minWeights)
                    ans[1].push_back(cur[idx]);
            }
        }
        return ans;
    }
};
