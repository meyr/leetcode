/*
 *  參考 : https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/solutions/730567/java-c-python-straight-forward/
 *  
 *  因為最多可以移除3個element 且一定是移除最大或是最小 則組合就有限了 列舉所有的組合
 *  
 *  移除最小3個 最大0個
 *  移除最小2個 最大1個
 *  移除最小1個 最大2個
 *  移除最小0個 最大3個
 *
 *  從這些組合中找出最小值
 *  time  : O(NlogN)
 *  space : O(logN)
 */

class Solution {
public:
    int minDifference(vector<int>& nums) {
        int sz = nums.size();
        if(sz < 5) return 0;
        sort(begin(nums), end(nums));
        return min({nums[sz - 1] - nums[3], 
                    nums[sz - 2] - nums[2], 
                    nums[sz - 3] - nums[1], 
                    nums[sz - 4] - nums[0]});
    }
};
