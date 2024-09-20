/*
 *  因為題目是從s的前面加上char讓他成為palindrome
 *  所以最worse case我一定可以加上 s.size() - 1的字串讓他成為palindrome
 *  ex : abcde   我一定可以加上s.substr(1) = "bcde" 的反向 edcb 使得 edcbabcde 成為palindrome
 *       ----
 *
 *  所以問題變成找出s中從0開始最長的palindrome則加上得 s.substr(i)就會最短     
 *  使用以下的方法可以找到但是
 *  time  : O(N^2)會 TLE
 *
 *  怎麼O(N)的方法找出最長的palindrome就會是關鍵
 */
class Solution {
    bool isPalindrome(string& s, int i, int j) {
        if(i == j) return true;
        while(i < j) {
            if(s[i++] != s[j--]) 
                return false;
        }
        return true;
    }
public:
    string shortestPalindrome(string s) {
        int sz = s.size(), i;
        for(i = s.size() - 1; i >= 0; --i) // 找出s中從0開始最長的palindrome
            if(isPalindrome(s, 0, i)) break;
        string rev_s = s.substr(i + 1);
        reverse(begin(rev_s), end(rev_s));
        return rev_s + s;
    }
};
/*  參考 : https://leetcode.cn/problems/shortest-palindrome/solutions/392561/zui-duan-hui-wen-chuan-by-leetcode-solution/
 *
 *  使用rolling hash找出最長的palindrome 
 *  ex: aacecaaa
 *      - a  a 
 *      -- aa aa
 *      --- aac caa
 *      ---- aace ecaa
 *      ----- aacec cecaa
 *      ------ aaceca acecaa
 *      ------- aacecaa aacecaa (match!)
 *
 *      left 部分 : 把最右邊當成p^0 這樣比較好計算    aaceca ->  a*p^5 + a*p^4 + c*p^3 + e*p^2 + c*p^1 + a*p^0          = val1
 *                                                    aacecaa->  a*p^6 + a*p^5 + c*p^4 + e*p^3 + c*p^2 + a*p^1 + a*p^0  = val1*p + a
 *
 *      right部分:                                    aacec[a]-> [a]cecaa = [a*p^5] + c*p^4 + e*p^3 + c*p^2 + a*p^1 + a*p^0          = val1
 *                                                    aaceca[a]->[a]acecaa= [a*p^6] + a*p^5 + c*p^4 + e*p^3 + c*p^2 + a*p^1 + a*p^0  = val1 + a*p^6
 *
 *      也可以參考 1392. Longest Happy Prefix
 *
 *      time  : O(N + N + N) = O(N)
 *      space : O(N)
 */
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        int base = 131, mod = 1000000007;
        int left = 0, right = 0, mul = 1;
        int best = -1;
        for (int i = 0; i < n; ++i) {
            left = ((long long)left * base + s[i]) % mod;
            right = (right + (long long)mul * s[i]) % mod;
            if (left == right) {
                best = i;
            }
            mul = (long long)mul * base % mod; // 計算 p^k
        }
        string add = (best == n - 1 ? "" : s.substr(best + 1, n));
        reverse(add.begin(), add.end());
        return add + s;
    }
};
