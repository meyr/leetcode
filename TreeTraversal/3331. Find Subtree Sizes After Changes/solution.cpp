/*
 *      看懂題目花了一點時間，
 *      題目是說同時把node換parent, 換parent的機制是往上找到和自己一樣的char
 *      如果找不到就不換parent
 *
 *      最後計算subtree(包含自己)的個數
 *
 *      因為同時進行所以使用last紀錄從這個node往上看會看到那些char的node
 *      這邊改過之後退出比須改回來 這就是prev存在的意義
 *
 *      time  : O(N)
 *      space : O(N)
 */

class Solution {
    void dfs(vector<int>& newp, vector<vector<int>>& childs, vector<int>& last, string_view s, int i) {
        if(last[s[i] - 'a'] != -1) newp[i] = last[s[i] - 'a'];
        int prev = last[s[i] - 'a'];
        last[s[i] - 'a'] = i;
        for(auto& c : childs[i])
            dfs(newp, childs, last, s, c);
        last[s[i] - 'a'] = prev;
    }
    int dfs2(vector<vector<int>>& childs, vector<int>& ans, int i) {
        if(childs[i].size() == 0) return ans[i] = 1;
        int count{1};
        for(auto& c : childs[i])
            count += dfs2(childs, ans, c);
        return ans[i] = count;
    }
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int sz = parent.size();
        vector<vector<int>> childs(sz, vector<int>());
        for(int i = 1; i < sz; ++i)
            childs[parent[i]].push_back(i);
        vector<int> last(26, -1);
        vector<int> newp(begin(parent), end(parent));
        dfs(newp, childs, last, s, 0);
        //for(auto& n : newp) cout << n << ",";
        //cout << endl;
        childs = move(vector<vector<int>>(sz, vector<int>()));
        for(int i = 1; i < sz; ++i)
            childs[newp[i]].push_back(i);
        vector<int> ans(sz);
        dfs2(childs, ans, 0);
        return ans;        
    }
};
