/*
 *
 *  time  : O(NlogN + N + MlogN) = O(NlogN + MlogN)
 *  space : O(N + M)
 */
class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        map<int, int> m;
        for(auto& it : items) { //O(NlogN)
            int p = it[0];
            int b = it[1];
            m[p] = max(m[p], b);
        }
        for(auto it = next(m.begin()); it != m.end(); ++it) // O(N)
            it->second = max(it->second, prev(it)->second);
        vector<int> ans;
        for(auto& q : queries) { // O(MlogN)
            auto it = m.upper_bound(q);
            int val{};
            if(it != m.begin())
                val = prev(it)->second;
            ans.push_back(val);
        }
        return ans;
    }
};
/*  另一個想法把queries也放進items一起排序
 *
 *  time  : O(M + (M+N)log(M+N) + M + N) = O((M+N)log(M+N))
 *  space : O(M + (M+N) + log(M+N)) = O(M+N)
 */
class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        int sz = queries.size();
        vector<int> ans(sz);
        for(int i = 0; i < sz; ++i) // O(M)
            items.push_back({queries[i], (int)(1e9 + i + 1)});
        int maxv{};
        sort(begin(items), end(items)); // O((M+N)log(M+N))
        for(auto& it : items) { // O(M + N)
            if(it[1] > 1e9) { // query
                int idx = it[1] - 1e9 - 1;
                ans[idx] = maxv;
            } else { // items
                maxv = max(maxv, it[1]);
            }
        }
        return ans;
    }
};
