/*  edges1 所構成的tree1 可以任意node連接一條path到由edges2所構成的 tree2
 *
 *  Greedy point : 連接到tree2當然是連到 path = k-1最多node的點
 *
 *  1. 找出tree1每個node經過k個path之後的node數
 *  2. 找出tree2每個node經過k-1個path之後的node數, 因為從tree1連過來少了一個path
 *  3. 找出tree2上最大node數, 加回tree1
 */
class Solution {
    int check(unordered_map<int, vector<int>>& adj, int prev, int cur, int k) {
        if(k == 0) return 1;
        int rtn{1};
        for(auto& nxt : adj[cur]) {
            if(nxt != prev)
                rtn += check(adj, cur, nxt, k - 1);
        }
        return rtn;
    }
    vector<int> helper(vector<vector<int>>& edges, int k) {
        int sz = edges.size();
        vector<int> rtn(sz + 1);
        unordered_map<int, vector<int>> adj;
        for(auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        for(int i = 0; i <= sz; ++i)
            rtn[i] = check(adj, -1, i, k);
        return rtn;
    }
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        int n = edges1.size(), m = edges2.size();
        if(k == 0) return vector<int>(n + 1, 1);    // special case 1, k == 0 只能達到自己 所以都是1
        vector<int> rtn1 = helper(edges1, k);
        if(k == 1) {                                // special case 2, k == 1 只能達到tree2一個點 所以全部都+1 不須計算tree2
            for(auto& n : rtn1)
                n++;
            return rtn1;   
        }
        vector<int> rtn2 = helper(edges2, k - 1);
        int maxv = *max_element(begin(rtn2), end(rtn2));
        for(int i = 0; i < n + 1; ++i)
            rtn1[i] += maxv;
        return rtn1;
    }
};
