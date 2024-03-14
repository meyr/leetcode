/*
 *   因為要找nums[i] <= nums[i + 1] 所以從後面開始找起
 *   因為後面的可以吃掉前面的 所以使用sum來比較
 *
 */
class Solution {
public:
    long long maxArrayValue(vector<int>& nums) {
        int sz = nums.size();
        if(sz == 1) return nums.front();
        long long ans{}, sum = nums.back();
        for(int i = nums.size() - 2; i >= 0; --i) {
            if(sum >= nums[i])
                sum += nums[i];
            else {
                ans = max(ans, sum);
                sum = nums[i];
            }
        }
        return max(ans, sum);
    }
};
