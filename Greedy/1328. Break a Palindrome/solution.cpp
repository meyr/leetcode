/* 
 * 因為要找出lexicographically smallest所以先從'a'開始試 且從index = 0 開始
 * 當找出可以取代的char和位置 還要判斷要放在前面還是後面 因為我們要找到lexicographically sammlest
 *
 *  time  : O(26 * N) = O(N)
 *  sapce : O(1)
 */
class Solution {
public:
    string breakPalindrome(string palindrome) {
        if(palindrome.size() == 1) return "";
        int sz = palindrome.size();
        for(char c = 'a'; c <= 'z'; ++c) {
            for(int i = 0; i < palindrome.size() / 2; ++i) {
                if(palindrome[i] != c) {
                    if(c > palindrome[i])               // __important 判斷是要放在前面還是後面
                        palindrome[sz - i - 1] = c;
                    else
                        palindrome[i] = c;
                    return palindrome;
                }
            }
        }
        return "";
    }
};
