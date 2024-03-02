/*
 *  參考lee215答案
 *  這邊的重點是怎麼處理prefix sum為負的情況
 *  如果(sum + nums[i]) % k 為負，因為要有循環效果
 *  所以必須加上k，所以為 (sum + nums[i]) % k + k
 *  但是sum + nums[i] 也有可能是正，如果加上k則可能超出範圍
 *  所以再mod一次k，即為((sum + nums[i]) % k + k) % k
 *
 */
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int sum{}, ans{};
        unordered_map<int, int> m; // mod k, count
        m[0] = 1;
        for(int i = 0; i < nums.size(); ++i) {
            sum =((sum + nums[i]) % k + k) % k;
            ans += m[sum];
            m[sum]++;
        }
        return ans;
    }
};
