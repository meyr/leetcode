/*
 *	time  : O(NlogN)
 *  space : O(logN)
 */
class Solution {
public:
    bool canSortArray(vector<int>& nums) {
        int idx = 0;
        while(idx < nums.size()) {
            int n = __builtin_popcount(nums[idx]);
            int nxt = idx + 1;
            while(nxt < nums.size() && __builtin_popcount(nums[nxt]) == n) nxt++;
            sort(begin(nums) + idx, begin(nums) + nxt);
            if(idx > 0 && nums[idx - 1] > nums[idx]) return false;
            idx = nxt;
        }
        return true;
    }
};
