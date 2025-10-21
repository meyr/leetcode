/* 
 * 嘗試所有的數字 找出最大頻率
 * 使用prefix sum來計算所有可能變成此數字的candidate 並且我們最多只能變numOperations個candidates
 *
 *  time  : O(N + N + N + N) = O(N)
 *  space : O(M), M : maximum value of nums
 */
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int maxv = *max_element(begin(nums), end(nums)); // O(N)
        vector<int> cnt(maxv + 2);
        for(auto& n : nums) cnt[n]++; // O(N)
        for(int i = 1; i < cnt.size(); ++i) cnt[i] += cnt[i - 1]; // O(N)
        int ans{};
        for(int i = 1, left = i - k - 1, right = min((int)cnt.size() - 1, k + 1); i < cnt.size(); ++i, ++left++, right++) { // O(N)
            int cur = cnt[i] - cnt[i - 1];
            int total = cnt[right] - (left >= 0 ? cnt[left] : 0);
            ans = max(ans, cur + min(numOperations, total - cur));
            right = min((int)cnt.size() - 1, right + 1);
            left++;
        }
        return ans;
    }
};
