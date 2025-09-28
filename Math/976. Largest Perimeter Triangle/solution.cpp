/*   為什麼只找相鄰的三個數字?
 *   因為已經排序過了 所以 nums[i] <= nums[i + 1] <= nums[i + 2]
 *   
 *   檢查 nums[i] + nums[i + 1] >= nums[i + 2] 如果是三角形就成立直接返回
 *   
 *   如果不成立 則 nums[i] + nums[i + 1] < nums[i + 2]
 *   使用更小的數值 nums[i - 1] + nums[i + 1] 因為nums[i - 1] < nums[i] 
 *   所以 nums[i - 1] + nums[i + 1] < nums[i] + nums[i + 1] < nums[i + 2]即使往下找還是不會成立
 *   所以只要找相鄰的三個數即可
 *
 *   time  : O(NlogN + N) = O(NlogN)
 *   space : O(1)
 */
class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        int ans{}, sz = nums.size();
        sort(begin(nums), end(nums));
        for(int i = sz - 3; i >= 0; --i) {
            if(nums[i] + nums[i + 1] > nums[i + 2])
                ans = max(ans, nums[i] + nums[i + 1] + nums[i + 2]);
        }
        return ans;
    }
};
