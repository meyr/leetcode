/*  因為題目要求O(logN) 直覺就想到binary search
 *  觀察範例 當從mid切開來看 可以分成基數和偶數的情況 會有不一樣
 *
    1, 1, 2, 2, 3, 3, 4, 8, 8
    1, 1, 2, 3, 3, 4, 4, 8, 8
                *  ---------- 4 (even)            

    3, 3, 5, 7, 7,  10, 10
    3, 3, 7, 7, 10, 11, 11
             *  ---------- 3 (odd)

    最後收斂到三個，下一次就會left == right
    1, 1, 2
    1, 2, 2
       *

 *
 *  time  : O(logN)
 *  space : O(1)
 */
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while(left < right) {
            int mid = left + (right - left) / 2;
            if((right - mid) % 2 == 0) {
                if(nums[mid] == nums[mid - 1]) right = mid;
                else left = mid;
            } else {
                if(nums[mid] == nums[mid - 1]) left = mid + 1;
                else right = mid - 1;
            }
        }
        return nums[left];
    }
};
/*
*/
