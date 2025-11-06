/*  先使用UnionFind找出每個group
 *  再統計每個group有誰
 *  最後根據queries來 取出online或是group最小id
 */

class Solution {
    vector<int> root, online, rank;
    unordered_map<int, set<int>> group;
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    int un(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return 0;
        if(rank[y] > rank[x]) swap(x, y);
        rank[x] += rank[y];
        return root[y] = x;
    }
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        root.resize(c + 1);
        online.resize(c + 1, 1);
        rank.resize(c + 1, 1);
        iota(begin(root), end(root), 0);
        for(const auto& conn : connections)
            un(conn[0], conn[1]);
        for(int i = 1; i <= c; ++i)
            group[find(i)].insert(i);
        vector<int> ans;
        for(const auto& q : queries) {
            int op = q[0], st = q[1];
            switch(op) {
                case 1:
                        if(online[st]) ans.push_back(st);
                        else {
                            st = find(st);
                            if(group[st].empty()) ans.push_back(-1);
                            else ans.push_back(*group[st].begin());
                        }
                        break;
                case 2:
                        online[st] = 0;
                        group[find(st)].erase(st);
                        break;
            }
        }   
        return ans; 
    }
};
