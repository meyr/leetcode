/* 一開始把問題想的太複雜 看了解答之後其實就是選擇問題
 *  1. 這個數字不納入s1 也不納入s2
 *  2. 這個數字納入s1 sequence
 *  3. 這個數字納入s2 sequence
 */
class Solution {
    int mod = 1e9 + 7;
    int helper(const vector<int>& nums, int i, int s1, int s2) {
        if(i == nums.size()) return ((s1 != 0) && (s1 == s2));
        else if(~mem[i][s1][s2]) return mem[i][s1][s2];
        // case 1 兩個sequence都不取
        long long rtn = helper(nums, i + 1, s1, s2);
        // case 2 納入s1 sequence
        rtn = (rtn + helper(nums, i + 1, s1 == 0 ? nums[i] : __gcd(s1, nums[i]), s2)) % mod;
        // case 3 納入s2 sequence
        rtn = (rtn + helper(nums, i + 1, s1, s2 == 0 ? nums[i] : __gcd(s2, nums[i]))) % mod;
        return mem[i][s1][s2] = rtn;
    }
    vector<vector<vector<int>>> mem;
public:
    int subsequencePairCount(vector<int>& nums) {
        mem.resize(nums.size() + 1, vector<vector<int>>(201, vector<int>(201, -1)));
        return helper(nums, 0, 0, 0);
    }
};
