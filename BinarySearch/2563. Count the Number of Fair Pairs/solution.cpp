/* 排序後使用binary search找出符合條件的數值
 *
 * time  : O(NlogN + NlogN) = O(NlogN)
 * space : O(logN)
 */
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(begin(nums), end(nums));
        long long ans{};
        for(int i = 0; i < nums.size(); ++i) {
            auto st = lower_bound(begin(nums) + i + 1, end(nums), lower - nums[i]);
            auto ed = upper_bound(begin(nums) + i + 1, end(nums), upper - nums[i]);
            ans += ed - st;
        }
        return ans;
    }
};
/*
 * 參考: https://leetcode.com/problems/count-the-number-of-fair-pairs/solutions/3174181/two-pointers-2/
 *
 * 既然nums已經排序了 所以[0, 1, 4, 4, 5, 7] 則所有pair的組合為
 *                        [0, 1], [0, 4], [0, 4], [0, 5], [0, 7]
 *                                [1, 4], [1, 4], [1, 5], [1, 7]
 *                                        [4, 4], [4, 5], [4, 7]
 *                                                [4, 5], [4, 7]
 *                                                        [5, 7]
 *                            -------------> j
 *                                            
 *                      |     1*, 4, 4, 5,  7*
 *                      |         5, 5, 6,  8
 *                      |            8, 9, 11
 *                      |               9, 11
 *                     \|/                 12
 *
 *                      i
 */
class Solution {
public:
    // 找出pair中nums[i] + nums[j] <= val的個數
    long long countLess(vector<int>& nums, int val) {
        long long res = 0;
        for (int i = 0, j = nums.size() - 1; i < j; ++i) { // 找出每一列 滿足nums[i] + nums[j] <= val的個數 但是j不用重找 因為nums[i]只會越來越大
            while(i < j && nums[i] + nums[j] > val)        // __important__ 結束條件式 i < j
                --j;
            res += j - i;
        }
        return res;
    }

    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(begin(nums), end(nums));
        return countLess(nums, upper) - countLess(nums, lower - 1); // 因為找出的是nums[i] + nums[j] <= val所以 lower要減一 包括lower
    }
};
