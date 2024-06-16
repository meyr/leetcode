/*
 *     參考 : https://leetcode.com/problems/patching-array/solutions/78492/c-8ms-greedy-solution-with-explanation/
 *
 *     這邊的重點是maxNum 當array可以組成數值的最大值為maxNum
 *
 *     如果nums[i] <= maxNum, 則表示這個數值可以被以前的值組合, 將nums[i]納入, 則maxNum就會被更新
 *     如果nums[i]  > maxNum, 表示中間有缺數字, 則納入maxNum + 1, 因為加入新數值, 所以更新maxNum
 *
 */
class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int ans{}, i{};
        long long maxNum{};
        while(maxNum < n) {
            if(i < nums.size() && nums[i] <= maxNum + 1)
                maxNum += nums[i++];
            else {
                maxNum += maxNum + 1;
                ans++;
            }
        }
        return ans;
    }
};
