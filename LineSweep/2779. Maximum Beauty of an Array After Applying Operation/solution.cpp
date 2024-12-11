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
    因為每個nums[i]都可以 +k, -k 所以某個subarray可以變成一個值(target)
    nums[i], nums[i + 1]... nums[j] 一定符合

    nums[i] + k1 = nums[j] - k2   其中k1, k2 <= k
    nums[j] - nums[i] = k1 + k2 <= 2 * k

    time  : O(NlogN + N) = O(NlogN)
    space : O(logN)
*/
class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));
        int ans{1};
        for(int left = 0, right = 0; right < nums.size(); ++right) {
            while(left < right && nums[right] - nums[left] > 2 * k)
                left++;
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};
