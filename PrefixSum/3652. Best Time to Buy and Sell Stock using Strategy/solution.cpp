/*   把profit計算分成三段
 *
 *        stategy : -1, 0, 1, 0, ..., 0, 0, ..., 0, 1, 1, ..., 1, ..., 0, 1, -1, 0
 *                                    |------------------------| 可以修改的window k 前半部是0 後半部是1 只需計算後半的prefix sum
 *                                     pfs[i] - pfs[i - k / 2]
 *
 *  windows前半部    |----------------|                        |-----------------|  windows 後半部
 *                      spfs[i - k/2]                            spfs.back() - spfs[i]
 *
 *  這三個部分都可以使用prefix sum來計算
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int sz = prices.size();
        long long ans{};
        vector<long long> spfs(sz), pfs(sz);
        ans = spfs[0] = prices[0] * strategy[0];
        pfs[0] = prices[0];
        for(int i = 1; i < sz; ++i) {
            spfs[i] += spfs[i - 1] + prices[i] * strategy[i];
            pfs[i] += pfs[i - 1] + prices[i];
            ans += prices[i] * strategy[i];
        }
        for(int i = k - 1; i < sz; ++i) {
            long long cur = spfs.back() - spfs[i];
            cur += i - k >= 0 ? spfs[i - k] : 0;
            cur += pfs[i] - pfs[i - k / 2];
            ans = max(ans, cur);
        }
        return ans;
    }
};
