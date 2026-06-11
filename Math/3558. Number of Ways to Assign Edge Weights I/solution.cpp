/*  這題的重點是看穿解答是2^(maxDepth - 1)
 *
 *  首先我們要找到一條最深的路徑 假設經過了五個node才到達最深的node
 *  (),(),(),(),()  也就有五個空格需要你填入 1或是2 因為結果要odd
 *                  所以是 C(5,1) + C(5, 3) + C(5, 5) = 2^(5 - 1)  這個結果是 2^(maxDepth - 1)
 *
 *  另一種不用數學的推導 進入最後一個node之前的組合式2^(maxDepth - 1) 如果是偶數 我最後一個node就選1
 *                                                                    如果是奇數 我最後一個node就選2
 *  所以答案是 2^(maxDepth - 1)
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    unordered_map<int, vector<int>> adj;
    int getMaxDepth(int cur, int parent, int depth) {
        if(cur != 1 && adj[cur].size() == 1) return depth;
        int rtn{};
        for(const auto& nxt : adj[cur]) {
            if(nxt != parent)
                rtn = max(rtn, getMaxDepth(nxt, cur, depth + 1));
        }
        return rtn;
    }

    int powmod(int b, int e, int m = 1e9 + 7) { // 計算(2^N) % mod
        if(e == 0) return 1;
        else if(e == 1) return b;
        else {
            int rtn = powmod(b, e / 2, m);
            return (1LL * rtn * rtn * (e % 2 ? b : 1)) % m;
        }
    }

public:
    int assignEdgeWeights(vector<vector<int>>& edges) {
        for(const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        int maxDepth = getMaxDepth(1, 0, 0);
        return powmod(2, maxDepth - 1);
    }
};
