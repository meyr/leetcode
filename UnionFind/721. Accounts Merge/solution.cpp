/*
 *  相同的email代表同一個user
 *  所以使用union find來連結email
 *
 */

class Solution {
    vector<int> root, rank;
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    void un(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return;
        if(rank[y] > rank[x]) swap(x, y);
        root[y] = x;
        rank[x] += rank[y];
    }
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, int> m2g; // mail to group
        unordered_map<int, string> g2n; // group to name
        for(auto& acc : accounts) {
            string& name = acc[0];
            for(int i = 1; i < acc.size(); ++i) {
                if(!m2g.count(acc[i])) {
                    int g = root.size();
                    root.push_back(g);
                    rank.push_back(1);
                    m2g[acc[i]] = g;
                    g2n[g] = name;                    
                }
                un(m2g[acc[1]], m2g[acc[i]]);
            }
        }
        unordered_map<int, int> m; // group id to index of ans
        vector<vector<string>> ans;
        for(auto& ref : m2g) {
            string mail = ref.first;
            int g = find(ref.second);
            if(!m.count(g)) {
                ans.push_back({g2n[g]});
                m[g] = ans.size() - 1;
            }
            ans[m[g]].push_back(mail);
        }
        for(auto& a : ans)
            sort(begin(a) + 1, end(a));
        
        return ans;
    }
};
