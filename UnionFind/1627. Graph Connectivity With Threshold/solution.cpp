/*     類似 2709. Greatest Common Divisor Traversal
 *
 *     找出每個數值的divisor，然後跟之前的divisor連接在一起。
 *
 */
class Solution {
    vector<int> root, rank;
    int find(int a) {
        return root[a] == a ? a : root[a] = find(root[a]);
    }
    int un(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return 0;
        if(rank[a] < rank[b]) swap(a, b);
        root[b] = a;
        return rank[a] += rank[b];
    }
    bool isConnected(int a, int b) {
        return find(a) == find(b);
    }
public:
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        if(threshold == 0) return vector<bool>(queries.size(), true);
        root.resize(n + 1);
        iota(begin(root), end(root), 0);
        rank.resize(n + 1, 1);
        unordered_map<int, int> m;
        m[1] = 1;
        for(int i = 2; i <= n; ++i) {
            for(int d = threshold + 1; d <= i / 2; ++d) {
                if(i % d != 0) continue;
                if(m.count(d)) un(i, m[d]);
                m[d] = i;
            }
            m[i] = i;
        }
        vector<bool> ans;
        for(auto& q : queries)
            ans.push_back(isConnected(q[0], q[1]));
        return ans;
    }
};
