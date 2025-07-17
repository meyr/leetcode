/*
 *  每一個node和前面組合起來會有k個可能 所以用vector<vector<int>> len(sz, vector<int>(k)); 來表示
 *
 *  time  : O(N^2)
 *  space : O(NK)
 */

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int sz = nums.size(), ans{};
        vector<vector<int>> len(sz, vector<int>(k));
        for(int i = 0; i < sz; ++i) {
            len[i][nums[i] % k] = 1;
            for(int j = 0; j < i; ++j) {
                int t = (nums[i] + nums[j]) % k;
                if(len[j][t] == 0) len[i][t] = 2; // num[i], nums[j]成為新的subsequence
                else len[i][t] = max(len[i][t], len[j][t] + 1); // 和之前的合併
                ans = max(ans, len[i][t]);
            }
        }
        return ans;
    }
};
/*
    參考其他解答
    因為(nums[j] + nums[i]) % k = r
    所以使用dp[r][nums[i]%k] 來表達 mod k == r的序列長度
    (prev+cur)%k = r
    prev%k + cur%k = r
    prev + cur%k = r
    prev = (r - cur%k + k)%k

    time  : O(NK)
    space : O(K^2)
*/
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        vector<vector<int>> dp(k, vector<int>(k, 0));
        int maxLen = 0;
        for (int num : nums) {
            num %= k;
            for (int r = 0; r < k; ++r) {
                int prev = (r - num + k) % k;
                maxLen = max(maxLen, dp[r][num] = dp[r][prev] + 1);
            }
        }

        return maxLen;
    }
};
