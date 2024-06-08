/*
 *  不能使用slinding window是因為不是找subarray的最大長度
 *  因為是求subarray sum所以使用prefix sum
 *  另外使用unordered_map來記錄曾經遇過的prefix sum % k
 *  因為要整除 所以要找 目前的prefix sum
 *  最後只記錄最早遇到的prefix sum index
 *
 *  time  : O(N)
 *  space : O(K)
 */
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m{{0, -1}}; // prefix sum % k, index
        long long cur{};
        for(int i = 0; i < nums.size(); ++i) {
            cur = (cur + nums[i]) % k;
            if(m.count(cur) && i - m[cur] >= 2)  return true; // 找出之前遇過的prefix sum則中間sum就是可以被k整除
            if(!m.count(cur)) m[cur] = i; // 只記錄最早遇到的prefix sum index            
        }
        return false;
    }
};
