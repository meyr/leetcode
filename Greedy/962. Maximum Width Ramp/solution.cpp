/*
 *  參考 : https://leetcode.cn/problems/maximum-width-ramp/solutions/3610/zui-da-kuan-du-po-by-leetcode/
 * 
 *  因為必須滿足i < j 且 nums[i] <= nums[j] 所以先固定一個nums 把他從小到大排序 在記錄遇到的數值中最小的index
 * 
 *  time  : O(N + NlogN + N) = O(NlogN)
 *  space : O(N)
 */
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int sz = nums.size();
        vector<int> idx(sz);
        iota(begin(idx), end(idx), 0);
        sort(begin(idx), end(idx), [&](int a, int b){
            if(nums[a] < nums[b]) return true;
            else if(nums[a] == nums[b]) return a < b; // __important__ 如果數值一樣就index小的排在前面
            else return false;
        });
        int ans{}, minidx = sz;
        for(auto& i : idx) {
            ans = max(ans, i - minidx);
            minidx = min(minidx, i);      // 紀錄目前遇到數值中最小的index
        }
        return ans;
    }
};
