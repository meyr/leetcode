/*
 * 排序後, 看看選了那些student可以滿足
 *
 *
 * 6, 0, 3, 3, 6, 7, 2, 7
 * 0, 2, 3, 3, 6, 6, 7, 7
 *
 * time  : O(NlogN + N) = O(NlogN)
 * space : O(logN)               
 */
class Solution {
public:
    int countWays(vector<int>& nums) {
        sort(begin(nums), end(nums)); //O(NlogN) 使用bucket sort可以降低time complexity, 但是增加space complexity
        int cnt{}, ans = (nums.front() > 0) + (nums.back() < nums.size());
        for(int i = 0, j = 1; i < nums.size() - 1; ++i, j++) { // O(N)
            ans += nums[i] < j && nums[i + 1] > j;
        }
        return ans;
    }
};
