/*  本來使用BFS來解 後來發現會遇到loop 結果是TLE
 *  後來意識到是Topological sort的問題 因為每個原料都是指向recipie 當全部的原料都有才可以組成
 *
 */
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        int sz = recipes.size();
        vector<int> ind(sz);
        unordered_map<string, vector<int>> m;       // 紀錄ingredient會是那些recipes的原料
        unordered_set<string> _supp;
        for(auto& s : supplies) _supp.insert(s);
        for(int i = 0; i < sz; ++i) {
            ind[i] = ingredients[i].size();
            for(auto& ig : ingredients[i]) {
                m[ig].push_back(i);             // ingredient -> 1, 3, 4...
                if(_supp.count(ig)) ind[i]--;   // 如果需要原料就在supplies裡面就把ind--
            }
        }
        queue<int> q;
        for(int i = 0; i < sz; ++i)
            if(ind[i] == 0) q.push(i);
        vector<string> rtn;
        while(!q.empty()) {
            int idx = q.front(); q.pop();
            string& r = recipes[idx];
            rtn.push_back(r);
            if(!m.count(r)) continue;
            for(auto& i : m[r]) {
                if(--ind[i] == 0)
                    q.push(i);
            }
        }
        return rtn;
    }
};
