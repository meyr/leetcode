/*
 * 參考解答 : https://leetcode.com/problems/k-divisible-elements-subarrays/solutions/1996294/o-n-2-rabin-karp-vs-trie/
 *
 * 因為hash不可逃避的就是collision問題 所以使用unordered_map來確定是否有collision
 * 
 */

class Solution {
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        int mod = 1e9 + 7, pow = 31, ans = 0, sz = nums.size();
        vector<int> cnt(sz), hash(sz);
        for(int len = 0; len < nums.size(); ++len) {
            unordered_map<int, vector<int>> s;
            auto isCollision = [&](const int& hash, int i){
                for(int j : s[hash]) {
                    // 比對在s中長度一樣的兩個subarray開頭分別為i, j是否相同
                    if(equal(begin(nums) + i, begin(nums) + i + len + 1, begin(nums) + j))
                        return true;
                }
                return false;
            };
            for(int i = 0; i + len < sz; ++i) {
                cnt[i] += nums[i + len] % p == 0;
                if(cnt[i] <= k) {
                    hash[i] = ((long long)hash[i] * pow + nums[i + len]) % mod;
                    if(!isCollision(hash[i], i)) {
                        s[hash[i]].push_back(i); // 存入hash和開頭index
                        ans++;
                    }
                }
            }
        }
        return ans;
    }
};
