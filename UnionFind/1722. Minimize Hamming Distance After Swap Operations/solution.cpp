/*
 * 因為是找group的問題 很自然地想到UnionFind
 * 每個swap就是每個element可以連結的點 使用union find把可以swap都連結起來
 *
 */
class UnionFind {
    int sz;
    vector<int> root, rank;
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
public:
    UnionFind(int _sz) : sz(_sz), root(sz), rank(sz, 1){
        iota(begin(root), end(root), 0);
    }
    int un(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return 0;
        if(rank[y] > rank[x]) swap(x, y);
        root[y] = x;
        return rank[x] += rank[y];
    }
    vector<int> getRoot()
    {
        for(int i = 0; i < sz; ++i)
            root[i] = find(i);
        return root;
    }
};
class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        UnionFind uf(source.size());
        for(auto& s : allowedSwaps)
            uf.un(s[0], s[1]);
        auto root = uf.getRoot();
        unordered_map<int,  unordered_map<int, int>> um;    //root, <value, count>
        for(int i = 0; i < source.size(); ++i) {
            um[root[i]][source[i]]++;
            um[root[i]][target[i]]--;
        }
        int ans{};
        for(auto& ref : um) { // <int, unordered_map<int, int>>
            int count{};
            for(auto& ref2 : ref.second)    // <int, int>
                count += abs(ref2.second);  // __important__ 必須取abs因為有正有負
            ans += count / 2;               // __important__ 兩個不一樣hamming distance = 1
        }
        return ans;
    }
};
