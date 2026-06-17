/*  參考官方解答 : https://leetcode.com/problems/process-string-with-special-operations-ii/solutions/8314393/process-string-with-special-operations-i-8fzn/
 *
 *  1. 先計算總長度 len 因為之後的操作都需要根據總長度
 *  2. 如果 k >= len 直接返回 '.'
 *  3. 從'#', '*', '%' 反向推導k會落在哪個char
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    char processStr(string s, long long k) {
        long long len = 0;
        for (auto c : s) {
            if (c == '*') len = max(0LL, len - 1);
            else if (c == '#') len *= 2;
            else if (c == '%') continue;
            else len++;
        }
        if (k >= len) return '.';

        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '*') len++;
            else if (s[i] == '#') {
                if (k >= len / 2) k -= len / 2;  // 落在後半部 就往前len/2
                len /= 2;
            } else if (s[i] == '%') k = len - k - 1;  // abcd(e) len = 5, k = 4 -> (e)dcba   k = len - k - 1
            else {
                len--;
                if (k == len) return s[i];      // __important__ 先從正向來思考 加入一個char, 這個char的index就是len, 之後len會加1, 也就是len = len + 1
                                                //               逆向的時候 先把len--, 再判斷 k 是否等於 len (也就是上面的逆向操作)
            }
        }
        return '.';
    }
};
