/*
 *   使用rolling hash來判斷prefix和suffix
 *   注意，前後兩邊的rolling hash算法有些不同
 *
 *   time  : O(N)
 *   space : O(1)
 */

class Solution {
public:
    string longestPrefix(string s) {
        int p = 31, m = 1e9 + 7;
        int sz = s.size(), pk{1}, ans{};
        long long hash1{}, hash2{};
        for(int i = 0; i < sz - 1; ++i) {
            hash1 = (hash1 + (long long)s[i] * pk % m) % m;
            hash2 = (hash2 * p % m + s[sz - i - 1]) % m;
            pk = (long long)pk * p % m;
            if(hash1 == hash2)  
                ans = max(ans, i + 1);
        }
        return s.substr(0, ans);
    }
};
/*
    a, b, a, b, a, b
   a*p^0          b*p^0
 a*p^0+b*p^1   a*p^0+b*p^1
  

*/
