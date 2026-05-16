/*  和153題目一樣只是多了duplicate
 *  因為duplicate會破壞原本的binary search 特性
 *  3, 4, 5, 1, 2, 3
 *  1, 0, 0, 1, 1, 1
 *
 *  所以遇到前後一樣就把前面的index往後移動
 *  只移前面是因為我們根據後面來判斷
 *
 *  time  : O(logN)
 *  space : O(1)
 */
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while(left < right && nums[left] == nums[right]) left++; 
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] <= nums.back()) right = mid;
            else left = mid + 1;
        }
        return nums[left];
    }
};
