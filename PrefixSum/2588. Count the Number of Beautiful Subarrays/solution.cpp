/*
 * subarray可以透過operation消除變成0就是 每個bit都是偶數個 
 * 統計每個bit是否為偶數個或是奇數個可以使用xor
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    long long beautifulSubarrays(vector<int>& nums) {
        unordered_map<int, int> m;
        m[0] = 1;
        int xorval{};
        long long ans{};
        for(auto& n : nums) {
            xorval ^= n;
            ans += m[xorval];
            m[xorval]++;
        }        
        return ans;
    }
};
