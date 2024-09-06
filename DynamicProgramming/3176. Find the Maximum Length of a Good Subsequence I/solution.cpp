/*
 *  題目的意思是找出最長的subsequence 使得其中最多k個nums[i] != nums[i + 1]
 *
 *  範例1中的解答 
 *  1, 2, 1, 1    k = 2
 *  ----
 *     ----
 *
 *                只有兩組nums[i] != nums[i + 1] 所以最長為4
 *
 *  使用DP如果遇到和前一個不一樣 有兩種case 1.   取 helper(nums, i, k - 1) + 1
 *                                          2. 不取 就是for loop繼續往下

 *            遇到和前一個一樣 一定取 helper(nums, i, k) + 1
 *
 *  time  : O(NK), N = sizeof(nums)
 *  space : O(NK) 
 *
 */
class Solution {
    int helper(vector<int>& nums, int idx, int k) {
        //if(idx == nums.size() - 1) return 0; // 已經選了直接return 0
        if(~mem[idx][k]) return mem[idx][k];
        int ans{};
        for(int i = idx + 1; i < nums.size(); ++i) {
            if(nums[i] != nums[idx]) {
                if(k > 0) 
                    ans = max(ans, helper(nums, i, k - 1) + 1);
            } else
                ans = max(ans, helper(nums, i, k) + 1);
        }
        return mem[idx][k] = ans;
    }
    vector<vector<int>> mem;
public:
    int maximumLength(vector<int>& nums, int k) {
        int ans{1};
        mem.resize(nums.size(), vector<int>(k + 1, -1));
        for(int i = 0; i <= k; ++i)
            mem.back()[i] = 0;
        for(int i = 0; i < nums.size() - 1; ++i)
            ans = max(ans, helper(nums, i, k) + 1);
        return ans;
    }
};
