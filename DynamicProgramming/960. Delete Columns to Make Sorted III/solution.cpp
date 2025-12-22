/* ref : https://leetcode.com/problems/delete-columns-to-make-sorted-iii/solutions/206861/c-7-lines-dp-on-n-m-by-votrubac-pe0i/
 *
 *  找最長的lexicographic order的方法 應用到vector<string> strs
 *
 *  b, a, b, c, a
 *  1, 1, 2, 3, 2    每個index i都往前找 只要 str[j] <= str[i] 就計算 dp[i] = max(dp[i], dp[j] + 1)
 *        j  i       for(int i = 0; i < sz; ++i)
 *                      for(int j = 0; j < i; ++j)
 *                          if(str[j] <= str[i])
 *                              dp[i] = max(dp[i], dp[j] + 1);
 *
 *  現在的情況是 vector<string> strs;
 *  所以變成 每個k 都要滿足 strs[k][j] <= strs[k][i] 才可以計算 dp[i] = max(dp[i], dp[j] + 1)
 *
 *
 *  time  : O(NNM)
 *  space : O(N)
 */
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int m = strs.size();
        int n = strs[0].size();
        vector<int> dp(n, 1);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                for(int k = 0; k <= m; ++k) {
                    if(k == m) dp[i] = max(dp[i], dp[j] + 1);   //__important__ 先判斷 k == m
                    else if(strs[k][j] > strs[k][i]) break;     //              避免strs[k][j] 會out of range
                }
            }
        }
        return n - *max_element(begin(dp), end(dp));
    }
};
