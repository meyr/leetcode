/*  仿照 3372. Maximize the Number of Target Nodes After Connecting Trees I
 *  結果是TLE
 *
 *  問題在於怎麼快速的計算 tree1每個node的數量
 */
class Solution {
    int check(unordered_map<int, vector<int>>& adj, int prev, int cur, int cur_pri, int tar_pri) {
        int rtn = cur_pri == tar_pri;
        for(auto& nxt : adj[cur])
            if(prev != nxt)
                rtn += check(adj, cur, nxt, cur_pri ^ 1, tar_pri);
        return rtn;
    }
    vector<int> helper(vector<vector<int>>& edges, int pri) {
        int sz = edges.size() + 1;
        unordered_map<int, vector<int>> adj;
        for(auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        vector<int> rtn(sz);
        for(int i = 0; i < sz; ++i)
            rtn[i] = check(adj, -1, i, 0, pri);
        return rtn;
    }
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        vector<int> rtn1 = helper(edges1, 0);
        vector<int> rtn2 = helper(edges2, 1);
        int maxv = *max_element(begin(rtn2), end(rtn2));
        for(auto& n : rtn1)
            n += maxv;
        return rtn1;
    }
};
/*  ref : https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/solutions/6098836/on-m-by-votrubac-foi3/
 *
 *  這邊是先標記even和odd 則even node數量都會相同
 *
 */
class Solution {
public:
    int dfs(int i, int p, const vector<vector<int>> &al, vector<bool> &parity, bool even = true) {
        int targets = even;     // target計算even node的數量   因為只有even會是1，所以最後target只會回傳even node的數量
        parity[i] = even;       // 標記目前的node是even還是odd
        for (int j : al[i])
            if (j != p)
                targets += dfs(j, i, al, parity, !even);
        return targets;
    }
    vector<vector<int>> adjacencyList(vector<vector<int>>& edges) {
        vector<vector<int>> al(edges.size() + 1);
        for (auto &e: edges) {
            al[e[0]].push_back(e[1]);
            al[e[1]].push_back(e[0]);
        }
        return al;
    }
    vector<int> maxTargetNodes(vector<vector<int>>& e1, vector<vector<int>>& e2) {
        int m = e1.size() + 1, n = e2.size() + 1;
        vector<bool> parity(m), ingnored(n);
        int even1 = dfs(0, -1, adjacencyList(e1), parity), odd1 = m - even1;
        int even2 = dfs(0, -1, adjacencyList(e2), ingnored), odd2 = n - even2;
        vector<int> res(m);
        for (int i = 0; i < m; ++i)
            res[i] = max(even2, odd2) + (parity[i] ? even1 : odd1);
        return res;
    }
};
