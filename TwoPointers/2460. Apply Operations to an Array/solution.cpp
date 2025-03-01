/*  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    vector<int> applyOperations(vector<int>& nums) {
        int sz = nums.size();
        vector<int> rtn(sz);
        int j = 0;
        for(int i = 0; i < sz - 1; ++i) {
            if(nums[i] == 0) continue;
            if(nums[i] == nums[i + 1]) {
                rtn[j++] = nums[i] * 2;
                nums[i + 1] = 0;
                i++;
            } else rtn[j++] = nums[i];
        }
        if(nums.back())
            rtn[j] = nums.back();
        return rtn;
    }
};
/*  也可以做到 space : O(1)
 */
class Solution {
public:
    vector<int> applyOperations(vector<int>& nums) {
        int sz = nums.size();
        int j = 0;
        for(int i = 0; i < nums.size() - 1; ++i) {
            if(nums[i] != 0) {
                if(nums[i] == nums[i + 1]) {
                    nums[j] = nums[i] * 2;
                    nums[i + 1] = 0;
                    i++;
                } else nums[j] = nums[i];
                j++;
            }
        }
        if(nums.back()) nums[j++] = nums.back();
        while(j < sz) nums[j++] = 0;
        return nums;
    }
};
