/*  找出subarray經過任意swap之後可以變成palindrome
 *
 *  檢查palindrome的特性    
 *  len = 1  -> 1           one element with 1 count (0001000)
 *  len = 2  -> 11, 22      one element with 2 count (0000000)
 *  len = 3  -> 212, 222    one element with 3 count,(0001000) 
 *                          one element with 2 count + one element with 1 count (0001000)
 *
 *  len = 4  -> 3223, 3333  one element with 4 count, (0000000)
 *                          one element with 2 count + one element with 2 count (0000000)
 *
 *  len = 5  -> 32123, 33133, 33333
 *                          one element with 5 count, (0001000)
 *                          one element with 4 count + one element with 1 count (0001000)
 *                          one element with 2 count + one element with 2 count + one element with 1 count (0001000)
 *
 *
 *  如果使用vector來統計不太好判斷
 *  因為是判斷element的奇數偶數 所以可以使用xor
 *  這樣只需判斷 pattern使否為 0000000 (都為偶數), 00010000(只有一個element為奇數)
 */

class Solution {
public:
    int longestAwesome(string s) {
        int res{}, cur{};
        unordered_map<int, int> m{{0, -1}};
        for(int i = 0; i < s.size(); ++i) {
            cur ^= 1 << (s[i] - '0');
            if(m.count(cur)) res = max(res, i - m[cur]);
            for(int a = 0; a < 10; ++a) {
                int target = cur ^ (1 << a);
                if(m.count(target))
                    res = max(res, i - m[target]);
            }
            if(!m.count(cur)) m[cur] = i;
        }
        return res;
    }
};
