/*
 *  參考解答
 *
 *  
 */
class UnionFind{
    vector<int> root, rank;
    int n;
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
public:
    UnionFind(int n) : root(n + 1), rank(n + 1, 1), n(n) {
        iota(begin(root), end(root), 0);
    }
    /*  因為為了__計算使用的edge__所以只要有拿來連線就返回1 否則返回0
     *  另外還要計算目前還有多少node還沒連接(n) 
     */
    int un(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b) return 0;
        n--;
        if(rank[b] > rank[a]) swap(a, b);
        root[b] = a;
        rank[a] += rank[b];
        return 1;
    }
    bool isTraversable() {
        return n == 1;
    }
};
class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        int need{}; // 計算需要edge的數量
        UnionFind alice(n), bob(n);
        for(auto& e : edges) { // Greedy point : 先取共同的edge這樣才可以使edge數量最小
            if(e[0] == 3)
                need += alice.un(e[1], e[2]) | bob.un(e[1], e[2]);
        }
        for(auto& e : edges) { // 再來連接alice和bob需要的edge
            if(e[0] == 1) need += alice.un(e[1], e[2]);
            else if(e[0] == 2) need += bob.un(e[1], e[2]);
        }
        if(alice.isTraversable() && bob.isTraversable())
            return edges.size() - need;
        else
            return -1;
    }
};
