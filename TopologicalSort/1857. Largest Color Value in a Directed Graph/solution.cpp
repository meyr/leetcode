/*  因為題目是directed graph且路徑有yclic的話就是invalid所以直覺使用topologic sort
 *  因為可以判斷的node數來看是否有cyclic 所以先不管color寫出第一版的solution
 */
class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int sz = colors.size(), ans{1}, processed{};
        vector<int> ind(sz);
        unordered_map<int, vector<int>> adj;
        for(auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            ind[e[1]]++;
        }
        queue<int> q;
        for(int i = 0; i < sz; ++i)
            if(ind[i] == 0)
                q.push(i);

        while(!q.empty()) {
            int cur = q.front(); q.pop();
            processed++;
            for(auto& nxt : adj[cur]) {
                if(--ind[nxt] == 0)
                    q.push(nxt);
            }
        }
        return processed == sz ? ans : -1;
    }
};
/*  加上color之後 變成以下的版本
 *
 */
class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int sz = colors.size(), ans{1}, processed{};
        vector<int> ind(sz);
        vector<vector<int>> st(sz, vector<int>(26)); // node, max color in current node
        unordered_map<int, vector<int>> adj, prev;
        for(auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            prev[e[1]].push_back(e[0]);
            ind[e[1]]++;
        }
        queue<int> q;
        for(int i = 0; i < sz; ++i)
            if(ind[i] == 0) {
                q.push(i);
                st[i][colors[i] - 'a']++;
            }

        while(!q.empty()) {
            int cur = q.front(); q.pop();
            processed++;
            for(auto& nxt : adj[cur]) {
                if(--ind[nxt] == 0) {
                    q.push(nxt);
                    for(auto& f : prev[nxt]) {              // __important__ 檢查所以來到此node的路徑 把最大值存起來
                        for(int i = 0; i < 26; ++i)
                            st[nxt][i] = max(st[nxt][i], st[f][i]);
                    }
                    ans = max(ans, ++st[nxt][colors[nxt] - 'a']);
                }
            }
        }
        return processed == sz ? ans : -1;
    }
};
/*
 *  參考: https://leetcode.cn/problems/largest-color-value-in-a-directed-graph/solutions/766070/you-xiang-tu-zhong-zui-da-yan-se-zhi-by-dmtaa/
 *  概念和上面一樣 只是更新每個node的color的時候是直接對下一個node更新
 *
 */
class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<vector<int>> g(n);
        vector<int> indeg(n);
        for (auto&& edge: edges) {
            ++indeg[edge[1]];
            g[edge[0]].push_back(edge[1]);
        }

        int found = 0;
        vector<array<int, 26>> f(n);    // 統計每個path到達此node的最大color數
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (!indeg[i])
                q.push(i);

        int ans{};
        while (!q.empty()) {
            ++found;
            int cur = q.front(); q.pop();
            ans = max(ans, ++f[cur][colors[cur] - 'a']);
            for (int nxt: g[cur]) {
                for (int c = 0; c < 26; ++c)
                    f[nxt][c] = max(f[nxt][c], f[cur][c]);

                if (--indeg[nxt] == 0)
                    q.push(nxt);
            }
        }

        return found == n ? ans : -1;
    }
};
