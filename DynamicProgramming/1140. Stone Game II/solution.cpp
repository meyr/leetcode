/*   因為alice和bob分別要得到最多stone
 *   所以是alice的時候max(rtn, sum + helper)
 *   如果是bob的話就要min(rtn, helper - sum)
 *
 *   time  : O(NN2) = O(N^2)
 *   space : O(NN) = O(N^2) 
 */
class Solution {
    enum player{
        alice,
        bob
    };
    int sz;
    int helper(vector<int>& piles, int idx, int M, int p) {
        if(idx >= piles.size()) return 0;
        else if(~mem[idx][M][p]) return mem[idx][M][p];
        int rtn = p == alice ? INT_MIN : INT_MAX;
        int sum{};
        for(int i = idx; i < idx + 2 * M && i < sz; ++i) {
            sum += piles[i];
            if(p == alice) rtn = max(rtn, sum + helper(piles, i + 1, max(M, i - idx + 1), !p));
            else rtn = min(rtn, helper(piles, i + 1, max(M, i - idx + 1), !p) - sum);
        }
        return mem[idx][M][p] = rtn;
    }
    vector<vector<vector<int>>> mem;
public:
    int stoneGameII(vector<int>& piles) {
        sz = piles.size();
        int total = accumulate(begin(piles), end(piles), 0);
        if(sz <= 2) return total; // special case
        mem.resize(sz, vector<vector<int>>(sz, vector<int>(2, -1)));
        return (helper(piles, 0, 1, 0) + total) / 2;;
    }
};
/*
 *  參考 : https://leetcode.com/problems/stone-game-ii/solutions/345395/c-0-ms/
 *
 */
class Solution {
public:
    int memo[101][32] = {};
    int dfs(vector<int>& dp, int x, int m, int res = INT_MIN) {
        if (x + m * 2 >= dp.size()) return dp.back() - dp[x - 1]; //全拿
        if (memo[x][m]) return memo[x][m];
        // 沒辦法全拿
        for (int i = x; i < x + m * 2 && i < dp.size(); ++i)
            res = max(res, dp[i] - (x == 0 ? 0 : dp[x - 1]) - dfs(dp, i + 1, max(m, i - x + 1)));
        //                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 從x到i的sum
        //                                                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 換bob所以用減的
        // 回到alice的時候 res = max(res, sum - (sum' - dfs())) = max(res, sum - sum' + dfs()) 所以dfs會變成正的
        return memo[x][m] = res;
    }
    int stoneGameII(vector<int>& ps) {
        partial_sum(begin(ps), end(ps), begin(ps));
        if(ps.size() <= 2) return ps.back();
        return (ps[ps.size() - 1] + dfs(ps, 0, 1)) / 2;
    }
};
