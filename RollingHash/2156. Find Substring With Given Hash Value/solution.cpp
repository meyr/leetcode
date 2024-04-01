/*
 *  參考解答 : https://leetcode.com/problems/find-substring-with-given-hash-value/solutions/1730321/java-c-python-sliding-window-rolling-hash/
 *  這題剛好是學習rolling hash的好機會
 *
 *  __從後面計算可以使用乘法__ 不然會有除法
 *
 *
 *  0, 1, 2, 3, 4, 5, 6, 7
 *  l, e, e, t, c, o, d, e
 *                [o, d, e] =                  val('o') * p^0 + val('d') * p^1 + val('e') * p^2 = val1
 *             [c, o, d]    = val('c') * p^0 + val('o') * p^1 + val('d') * p^2                  = val1 * p + val('c') * p^ 0 - val('e') * p^3
 *                                                                                                |_________________________|1  
 *                                                                                                                          |________________| 2                                               
 *  time  : O(N)
 *  space : O(1)
 */

class Solution {
public:
    string subStrHash(string s, int p, int m, int k, int hashValue) {
        long long cur = 0, res = 0, pk = 1, n = s.size();
        for(int i = n - 1; i >= 0; --i) {
            cur = (cur * p + s[i] - 'a' + 1) % m;  // 1
            if(i + k >= n) // 計算power^(k - 1)
                pk = pk * p % m;
            else // 因為減掉某個值會出現負值 所以+m再取modulo
                cur = (cur - (s[i + k] - 'a' + 1) * pk % m + m) % m; // 2            
            if(cur == hashValue)
                res = i;
        }
        return s.substr(res, k);
    }
};
