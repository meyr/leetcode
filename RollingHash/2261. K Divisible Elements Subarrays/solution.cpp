/*
 * 參考解答 : https://leetcode.com/problems/k-divisible-elements-subarrays/solutions/1996294/o-n-2-rabin-karp-vs-trie/
 * 
 * 因為nums.size() <= 200 所以可以使用O(N^2)來解答
 * 這邊的重點是判斷subarray是否重複
 *
 * vector<int> cnt(sz), hash(sz);
 * 其中cnt[i], hash[i] 表示從i開始的subarray
 * 檢查每個從i開始長度為len的subarray
 *
 * 把每個新加入的nums[i + len]視為第一項 所以rolling hash = (hash * pow + nums[i + len]) % mod;
 */

class Solution {
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        int sz = nums.size(), res{}, mod = 1e9 + 7, pow = 200;
        vector<int> cnt(sz), hash(cnt);
        for(int len = 0; len < nums.size(); ++len) {
            unordered_set<int> s; // 因為長度不同視為不同的subarray
            for(int i = 0; i + len < nums.size(); ++i) {
                cnt[i] += nums[i + len] % p == 0;
                if(cnt[i] <= k) {
                    hash[i] = ((long long)hash[i] * pow + nums[i + len]) % mod;
                    res += s.insert(hash[i]).second; // [iterator, bool] insert();
                                                    // 如果之前沒有則會insert成功
                                                    // 計算不重複的個數
                }
            }
        }
        return res;
    }
};
/*
    2,  3, 3, 2, 2
                          i = 0, i + len 為目前要處理的index
    [2]                   len = 0
    2, [3]                len = 1
    2, 3, [3]             len = 2
    2, 3, 3, [2]          len = 3
    2, 3, 3, 2, [2]       len = 4

                          i = 1
       [3],               len = 0
       3, [3]             len = 1
       3, 3, [2]          len = 2
       3, 3, 2, [2]       len = 3

*/
