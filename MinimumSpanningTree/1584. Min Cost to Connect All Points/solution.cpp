/*
 *   Minimum Spanning Tree  = Union Find + Priority Queue
 *
 */
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
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int sz = points.size();
        auto dist = [&](auto& a, auto& b){  // manhattan distance
            return abs(points[a][0] - points[b][0]) + abs(points[a][1] - points[b][1]); 
        };
        auto cmp = [&](auto& a, auto& b){   // edge = [index a, index b] in points
            return dist(a[0], a[1]) > dist(b[0], b[1]);
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        for(int i = 0; i < points.size(); ++i)              // 把所有可能的edge都放進pq
            for(int j = i + 1; j < points.size(); ++j)
                pq.push({i, j});

        int cost{};
        UnionFind uf(sz);       // 使用unfion find來找出是否連接完成
        while(!pq.empty()) {
            vector<int> cur = pq.top(); pq.pop();
            int rtn = uf.un(cur[0], cur[1]);
            if(rtn > 0 ) cost += dist(cur[0], cur[1]);
            if(rtn == sz) break;
        }
        return cost;
    }
};
