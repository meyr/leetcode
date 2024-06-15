/*
 *  因為每個element可以調整的範圍為[nums[i] - k, nums[i] + k] 等於是一個線段  
 *    4, 6, 1, 2
 *     2----6
 *         4----8
 * -1----3
 *   0-----4
 *  
 *  所以使用line sweep來統計最多的數字
 *  time  : O(NlogN + 2N) = O(NlogN)
 *  space : O(2N) = O(N)
 */
class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        map<int, int> m; // O(2N)
        for(auto& n : nums) { // O(NlogN)
            m[n - k]++;
            m[n + k + 1]--;
        }
        int ans{}, cur{};
        for(auto& ref : m) { // O(2N)
            ans = max(ans, cur += ref.second);
        }
        return ans;
    }
};
/*
*/
