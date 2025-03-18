/* subarray中任兩個element的AND都為0 
 * 所以使用unordered_map來統計每個bit的個數 
 * 只要有一個bit個數大於1 條件就不會成立
 *
 * time  : O(32N) = O(N)
 * space : O(1)
 */
class Solution {
    int helper(unordered_map<int, int>& um, int val, int op) {
        int rtn{};
        for(int i = 0; i < sizeof(int) * 8; ++i) {
            if((val >> i) & 1)
                um[i] += op;
            if(um[i] > 1)
                rtn |= 1 << i;
        }
        return rtn;
    }
public:
    int longestNiceSubarray(vector<int>& nums) {
        int ans{};
        unordered_map<int, int> um; // bit, count
        for(int left = 0, right = 0; right < nums.size(); ++right) {
            int result = helper(um, nums[right], 1);
            if(!result)
                ans = max(ans, right - left + 1);
            while(left < right && result) {
                result = helper(um, nums[left], -1);
                left++;
            }
        }
        return ans;
    }
};
/*  重點是統計每個bit是否有set bit所以只需要使用一個mask來統計每個set bit
 *
 *
 */
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int mask{}, ans{};
        for(int left = 0, right = 0; right < nums.size(); ++right) {
            while(mask & nums[right])   // 目前的mask和nums[right] 有重複的set bit, 移動left
                mask ^= nums[left++];
            ans = max(ans, right - left + 1);
            mask |= nums[right];        // 把目前的nums[right]放進mask
        }
        return ans;
    }
};
