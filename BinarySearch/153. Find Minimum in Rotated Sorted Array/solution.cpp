/*  一開始又亂寫 沒好好想解法 導致答案錯的亂七八遭 這也是我的問題 一拿到題目就開始寫 沒擬定好策略
 *
 *  題目說要使用O(logN)的time complexity 直覺就是使用binary search但是就是寫不出來
 *  3, 4, 5, 1, 2
 *
 *        *
 *      /
 *     *        *
 *   /        /
 *  *        *
 *
 *  我一開始用前後判斷
 *  [3, 4][4, 5][5, 1][1, 2]
 *    add   add   sub   add   --> +, +, +, -, +, +   這樣根本無法使用binary search
 *
 *  參考 : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/solutions/8232018/trick-question-by-la_castille-r3pi/
 *  如果和最後一個element比才可以變成 0, 0, [0, 1], 1 --> 這個形式才可以使用binary search, 轉折點的前後必須有一致的特性
 *                                              *                                          像這邊是前面是比最後element大 後面是比最後element小
 *
 *  有了策略寫code就簡單多了
 *
 *  time  : O(logN)
 *  space : O(1)
 */
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] < nums.back()) right = mid;
            else left = mid + 1;
        }
        return nums[left];
    }
};
