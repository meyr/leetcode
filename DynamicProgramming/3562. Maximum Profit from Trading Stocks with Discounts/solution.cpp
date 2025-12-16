/*  https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts/solutions/6778488/detailed-editorial-tree-dp-dfs-c-python-7095o/
 *
 *  . node u 狀態 :  state = 0 : node u不享受折扣  dp[u][state][budget]  在node u 不同的budget不同的state可以獲得的最大profit
 *                   state = 1 : node u  享受折扣 
 *    
 *
 *  . why post order traverse? 一個node狀態和subtree有關 和parent無關 因為我們使用了state來描述可不可以享折扣了 所以使用post order traverse
 *                             既然是post order 所以答案是 dp[0][0][budget] node 0不可能享受折扣所以state = 0, 且使用了最大的budget
 */
class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        vector<vector<int>> tree(n);
        for (const auto& edge : hierarchy) {
            tree[edge[0] - 1].push_back(edge[1] - 1);
        }

        // dp[node][parentBought][budget]
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(budget + 1, 0)));
        dfs(0, present, future, tree, dp, budget);

        int ans = 0;
        for (int b = 0; b <= budget; ++b) {
            ans = max(ans, dp[0][0][b]);
        }
        return ans;
    }

private:
    void dfs(int u, const vector<int>& present, const vector<int>& future,
             const vector<vector<int>>& tree, vector<vector<vector<int>>>& dp, int budget) {
        // Store children dp
        vector<pair<vector<int>, vector<int>>> childDPs;    // 所有的subtree dp[v][0] 和 dp[v][1]的組合

        for (int v : tree[u]) {
            dfs(v, present, future, tree, dp, budget);
            childDPs.emplace_back(dp[v][0], dp[v][1]);
        }

        for (int parentBought = 0; parentBought <= 1; ++parentBought) { // parentBought == 0 , 不享折扣. parentBought == 1 享折扣
            int price = parentBought ? present[u] / 2 : present[u];
            int profit = future[u] - price;

            vector<int> curr(budget + 1, 0);

            // Option 1: don't buy u
            vector<int> base(budget + 1, 0);        // 不購買u 則所有profit都來自child
            for (const auto& child : childDPs) {
                vector<int> next(budget + 1, 0);
                for (int b1 = 0; b1 <= budget; ++b1) {          // 把budget拆成兩分 b1, b2. b1在node u使用 b2在subtree使用
                    if (base[b1] == 0 && b1 != 0) continue;
                    for (int b2 = 0; b1 + b2 <= budget; ++b2) {
                        next[b1 + b2] = max(next[b1 + b2], base[b1] + child.first[b2]); // child.first 不享折扣
                    }
                }
                base = move(next);
            }

            for (int b = 0; b <= budget; ++b) {
                curr[b] = max(curr[b], base[b]);
            }

            // Option 2: buy u
            if (price <= budget) {                          // 目前的budget購買node u價格是price
                vector<int> baseBuy(budget + 1, 0);
                for (const auto& child : childDPs) {
                    vector<int> next(budget + 1, 0);
                    for (int b1 = 0; b1 <= budget; ++b1) {  // 雖然也是把budget拆成兩分 但是最後只會取b >= price的情況
                        if (baseBuy[b1] == 0 && b1 != 0) continue;
                        for (int b2 = 0; b1 + b2 <= budget; ++b2) {
                            next[b1 + b2] = max(next[b1 + b2], baseBuy[b1] + child.second[b2]);
                        }
                    }
                    baseBuy = move(next);
                }

                for (int b = price; b <= budget; ++b) {                     // __important__ 只考慮 b >= price情況
                    curr[b] = max(curr[b], baseBuy[b - price] + profit);
                }
            }

            dp[u][parentBought] = move(curr);
        }
    }
};
