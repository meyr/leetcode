/* 使用two pointer 一個指向開頭 一個從中間開始
 *
 * time  : O(NlogN + N) = O(NlogN)
 * sapce : O(logN)
 */
class Solution {
public:
    int maxNumOfMarkedIndices(vector<int>& nums) {
        sort(begin(nums), end(nums));
        int ans{}, sz = nums.size();
        int i{}, j = sz / 2;
        while(i < sz / 2 && j < sz) {
            while(j < sz && 2 * nums[i] > nums[j]) j++;
            ans += (j < sz) * 2;
            i++; j++;
        }
        return ans;
    }
};
