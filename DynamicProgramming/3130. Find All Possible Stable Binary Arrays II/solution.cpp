/*  這題是"3129. Find All Possible Stable Binary Arrays I"的進階版
 *  0 <= one, zero, limit <= 1000 --> 如果以以前的做法O(N^3) 會TLE
 *
 *  觀察 3129的解答 先把他轉成bottom-up tabulation的作法
 */
class Solution {
    using ll = long long;
    int limit, mod = 1e9 + 7;
    int helper(int zero, int one, int prev) {
        if(~mem[zero][one][prev]) return mem[zero][one][prev];
        int rtn{};
        if(prev == 0)
            for(int i = 1; i <= min(limit, one); ++i)
                rtn = ((ll)rtn + helper(zero, one - i, 1)) % mod;
        else
            for(int i = 1; i <= min(limit, zero); ++i)
                rtn = ((ll)rtn + helper(zero - i, one, 0)) % mod;
        return mem[zero][one][prev] = rtn;
    }
    // f(zero, one, 0) = sum(f(zero, one - i, 1)), i = [1, min(limit, one)]
    // f(zero, one, 1) = sum(f(zero - i, one, 0)), i = [1, min(limit, zero)]
    vector<vector<vector<int>>> mem;
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        this->limit = limit;
        mem.resize(zero + 1, vector<vector<int>>(one + 1, vector<int>(2, -1)));
        mem[0][0][0] = mem[0][0][1] = 1;
        return (helper(zero, one, 0) + helper(zero, one, 1)) % mod;
    }
};
/*  即使改成buttom-up 但是複雜到還是O(N^3)
 *
 */
class Solution{
    using ll = long long;
    constexpr int mod = 1e9 + 7;
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        vector<vector<vector<ll>>> dp(zero + 1, vector<vector<ll>>(one + 1, vector<ll>(2, 0)));

        for (int i = 0; i <= min(limit, zero); i++)     //__important__ 前一個是1 而且已經沒有1了 所以只能填連續0 這樣的substring只有一種
            dp[i][0][1] = 1;

        for (int i = 0; i <= min(limit, one); i++)      //__important__ 前一個是0 而且已經沒有0了 所以只能填連續1 這樣的substring只有一種
            dp[0][i][0] = 1;

        for (int i = 1; i <= zero; i++) for (int j = 1; j <= one; j++) {
            for (int k = 1; k <= limit && i - k >= 0; k++) {
                dp[i][j][1] += dp[i - k][j][0];                         // 前一個是1之後只能接0 f(zero, one, 1) = sum(f(zero - i, one, 0)), i = [1, min(limit, zero)]
                dp[i][j][1] %= mod;
            }
            for (int k = 1; k <= limit && j - k >= 0; k++) {
                dp[i][j][0] += dp[i][j - k][1];                         // 前一個是0之後只能接1 f(zero, one, 0) = sum(f(zero, one - i, 1)), i = [1, min(limit, one)]
                dp[i][j][0] %= mod;
            }
        }
        return (dp.back().back()[0] + dp.back().back()[1]) % mod;
    }
};
/*  仔細觀察 dp[i][j][1] 是一個slinding window sum
 *
 *                                  dp[i][j][0]   =               dp[i][j-1][1] + dp[i][j-2][1] + ... + dp[i][j-limit][1]
 *                                  dp[i][j+1][0] = dp[i][j][1] + dp[i][j-1][1] +                 ... + dp[i][j-limit][1] + dp[i][j-limit][1]
 *
 *                                  如果使用prefix sum這樣只要一值計算sum[i][j]
 *                                  sum[i][j] = dp[i][0][1] + dp[i][1][1] + ...+ dp[i][j][1],       sum[i][j]是描述prev = 0的時候__i固定__, j從0 ~ j - 1的總和
 *
 *                                  slinding window sum只要使用前後prefix sum來求得
 *                                  所以 dp[i][j][0] = sum[i][j - 1] - sum[i][j - limit - 1]
 *
 *  以下是參考gemini解答
 *
 *  time  : O(N^2)
 *  space : O(N^2)
 */
class Solution {
    using ll = long long;
    constexpr int mod = 1e9 + 7;

public:
    int numberOfStableArrays(int zero, int one, int limit) {
        // dp[i][j][0] 表示結尾為 0，dp[i][j][1] 表示結尾為 1
        vector<vector<vector<ll>>> dp(zero + 1, vector<vector<ll>>(one + 1, vector<ll>(2, 0)));

        // s0[i][j] 固定 j (one)，對 i (zero) 做前綴和，優化 dp[...][j][1] 的計算
        vector<vector<ll>> s0(zero + 1, vector<ll>(one + 1, 0));
        // s1[i][j] 固定 i (zero)，對 j (one) 做前綴和，優化 dp[i][...][0] 的計算
        vector<vector<ll>> s1(zero + 1, vector<ll>(one + 1, 0));

        for (int i = 0; i <= zero; i++) {
            for (int j = 0; j <= one; j++) {
                // --- 基礎案例 (Base Cases) ---
                if (i == 0 && j == 0) {
                    // 空集合不計入，但為了前綴和遞迴邏輯穩定，可保持 0
                    continue;
                }
                // 只有 0 的情況
                if (j == 0) {
                    if (i <= limit) dp[i][j][0] = 1;
                }
                // 只有 1 的情況
                else if (i == 0) {
                    if (j <= limit) dp[i][j][1] = 1;
                }
                else {
                    // --- 核心轉移 (DP Transition with Prefix Sum) ---
                    // 計算 dp[i][j][0] (最後填 0)
                    // 原本是 sum(dp[i-k][j][1] for k in 1..limit)
                    // 改用前綴和：s0[i-1][j] - s0[i-limit-1][j]
                    int lower_i = max(0, i - limit);
                    ll part0 = (s0[i - 1][j] - (lower_i > 0 ? s0[lower_i - 1][j] : 0) + mod) % mod;     // __important__ 因為有減所以(x + mod) % mod
                    dp[i][j][0] = part0;

                    // 計算 dp[i][j][1] (最後填 1)
                    // 原本是 sum(dp[i][j-k][0] for k in 1..limit)
                    // 改用前綴和：s1[i][j-1] - s1[i][j-limit-1]
                    int lower_j = max(0, j - limit);
                    ll part1 = (s1[i][j - 1] - (lower_j > 0 ? s1[i][lower_j - 1] : 0) + mod) % mod;
                    dp[i][j][1] = part1;
                }

                // --- 更新前綴和 (Update Prefix Sums) --- (繼續加入dp[i][j][0/1])
                s0[i][j] = ((i > 0 ? s0[i - 1][j] : 0) + dp[i][j][1]) % mod;
                s1[i][j] = ((j > 0 ? s1[i][j - 1] : 0) + dp[i][j][0]) % mod;
            }
        }

        return (dp[zero][one][0] + dp[zero][one][1]) % mod;
    }
};
