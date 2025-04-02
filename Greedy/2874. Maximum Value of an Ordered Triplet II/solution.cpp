/*	參考解答： 
 *	https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/solutions/6586318/maximum-value-of-an-ordered-triplet-ii-b-o8mj/
 *  
 *  1. k 為目前所在的index 往左看看到最大的dmax(nums[i] - nums[j])
 *  2. 更新dmax因為imax - nums[k] 有可能形成最大差
 *  3. 更新imax因為nums[k]有可能成為最大值
 *         下一個index看到的dmax還是正確的，因為dmax已經在imax之前更新過了
 *         直到遇到下一個nums[k]使得imax - nums[k] > dmax才會更新
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        long long res{}, imax{}, dmax{};
        for(int k = 0; k < nums.size(); ++k) {
            res = max(res, dmax * nums[k]);
            dmax = max(dmax, imax - nums[k]);
            imax = max(imax, (long long)nums[k]);
        }    
        return res;
    }
};
