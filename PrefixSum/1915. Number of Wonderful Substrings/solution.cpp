/*   
 *   一開始我使用slinding window 但是馬上意識到是錯的方法
 *    使用prefix sum的方法 
 *
 *    有兩種情況的subarray
 *    1. 沒有odd number char 就是可以在之前找到和目前val一樣
 *    2. 只有一個odd number char 就是可以在之前找到 (1<<i) ^ val
 *
 *    time  : O(N)
 *    space : O(1)
 */

class Solution {
public:
    long long wonderfulSubstrings(string word) {
        unordered_map<int, int> m;// value, count
        m[0] = 1;
        int val{};
        long long ans{};
        for(auto& c : word) {
            val ^= 1 << (c - 'a');
            ans += m[val]; // 沒有odd number char
            for(int i = 0; i < 10; ++i)
                ans += m[(1 << i) ^ val]; // 只有一個odd number char
            m[val]++;
        }
        return ans;
    }
};
