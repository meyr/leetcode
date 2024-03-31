/*
 *   參考解答 : https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/4949092/sliding-window-41ms-beats-100/
 *
 *   計算subarray的個數，可以參考下面的說明
 *   如果沒找到maxi或是mini，則min(maxi, mini) - l + 1 必為負，所以取max(*, 0)
 */
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int sz = nums.size(), maxi = -1, mini = -1; 
        long long ans{};
        for(int l = 0, r = 0; r < nums.size(); ++r) {
            if(nums[r] < minK || nums[r] > maxK)
                l = r + 1;
            else {
                if(nums[r] == maxK) maxi = r;
                if(nums[r] == minK) mini = r;
                ans += max((min(maxi, mini) - l + 1), 0);
            }
        }
        return ans;
    }
};
/*
     0   1  2  3  4  5
    [1, 3, 5, 2, 7, 5]

    [left, *, *, minK, *, *, maxK, *, *, right]

            min(mini, maxi)
                  |
                 \|/
    [left, *, *, minK, *, *, maxK, *, *, right]
          [*, *, minK, *, *, maxK, *, *, right]
             [*, minK, *, *, maxK, *, *, right]
                [minK, *, *, maxK, *, *, right]
         
*/
