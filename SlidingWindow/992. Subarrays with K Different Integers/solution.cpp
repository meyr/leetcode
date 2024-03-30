/*
 *   一開始使用sliding window想寫出剛好是k的解答 但是意識到會有考慮不到的情況
 *   請參考下面的說明
 *
 *   所以想到可以找 subarray different integer <= k 的會比較好找
 *
 */

class Solution {
    int helper(vector<int>& nums, int k) { // <= k
        unordered_map<int, int> m;
        int ans{};
        for(int left = 0, right = 0; right < nums.size(); ++right) {
            m[nums[right]]++;
            while(left < right && m.size() > k) {
                m[nums[left]]--;
                if(m[nums[left]] == 0)
                    m.erase(nums[left]);
                left++;
            }
            ans += right - left + 1;
        }
        return ans;
    }
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return helper(nums, k) - (k == 1 ? 0 : helper(nums, k - 1));
    }
};
/*
    [1, 2, 1, 2, 3]
    [1]
    [1, 2] ans++;
    [1, 2, 1] ans++;
       [2, 1] ?
    [1, 2, 1, 2] ans++;
       [2, 1, 2] ?
          [1, 2] ?
    [1, 2, 1, 2, 3]
       [2, 1, 2, 3]
          [1, 2, 3]
              [2, 3] ans++;

*/
