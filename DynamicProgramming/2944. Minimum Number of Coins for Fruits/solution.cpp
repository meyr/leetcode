/* 一開始使用DP的方式來解
 *
 * time  : O(N^2), up jo4 因為helper裡面還有個for loop
 * space : O(N)
 */
class Solution {
    int sz;
    int helper(vector<int>& prices, int idx) {
        if(idx >= sz) return 0;
        else if(~mem[idx]) return mem[idx];
        int rtn = 1e9;
        for(int i = idx + 1; i <= idx + (idx + 1) + 1; ++i)
            rtn = min(rtn, helper(prices, i) + prices[idx]);
        return mem[idx] = rtn;
    }
    // // f(i) = f(i+1, i+2, ..., (i+1)*2)
    vector<int> mem;
public:
    int minimumCoins(vector<int>& prices) {
        sz = prices.size();
        mem.resize(sz, -1);
        return helper(prices, 0);
    }
};
/* 改成建表
 *
 *  time  : O(N^2)
 *  space : O(N)
 */
class Solution {
public:
    int minimumCoins(vector<int>& prices) {
        int sz = prices.size();
        vector<int> dp(sz + 1, 1e9);
        dp.back() = 0;
        for(int i = sz - 1; i >= 0; --i) {
            for(int j = i + 1; j <= sz && j <= (i+1) * 2; ++j) // j : [i+1, (i+1)*2]  
                dp[i] = min(dp[i], dp[j] + prices[i]);
        }

        return dp[0];
    }
};
/*
 * 會有O(N^2)是因為尋找最小值的for loop
 * 可以使用deque<vector<int>>來找最小值
 *
 * time  : O(N)
 * space : O(N)
 */
class Solution {
    enum type{
        value,
        index
    };
public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        deque<vector<int>> q;
        q.push_front({0, n});
        for (int i = n - 1; i >= 0; i--) {
            while (!q.empty() && q.back()[index] > (i + 1) * 2) q.pop_back(); // 參考上面 先把範圍掉出(i+2)*2 丟掉
            int cur = q.back()[value] + prices[i];                            // 因為deque是從大到小排列 所以取最後面
            while (!q.empty() && cur < q.front()[value]) q.pop_front();       // 放入目前的值 但是必須維持從大到小 所以丟掉比自己大的, 使用val比較是因為 dp[i] = dp[j] + prices[i];
            q.push_front({cur, i});
        }
        return q.front()[value];
    }
};
