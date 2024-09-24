/*
 *  參考: https://leetcode.cn/problems/maximize-number-of-subsequences-in-a-string/solutions/2921910/zi-fu-chuan-zhong-zui-duo-shu-mu-de-zi-x-iv6p/
 *
 *  題目說只能在text加上一個 pattern[0] 或是 pattern[1]
 *
 *  在還沒加上一個char之前 計算符合的subsequence 每遇到一次pattern[1] 就把之前遇到過pattern[0]數目加起來
 *                   
 *  Greedy point : 因為只能加一個char 要加哪一個比較好? 如果pattern[0] size > pattern[1] 就加上pattern[1] 因為這樣會得到最大的結果
 *                                                      相同pattern[1] size > pattern[0] 就加上pattern[0]
 *
 *                 至於加上的位置一定是最前面pattern[0]或是最後面pattern[1] 這樣可以組成最多的subsequence
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    long long maximumSubsequenceCount(string text, string pattern) {
        long long res = 0;
        int cnt1 = 0, cnt2 = 0;
        // res 計算未加入char之前 所有符合pattern的subsequence
        for (char c: text) {
            if (c == pattern[1]) {
                res += cnt1;
                cnt2++;
            }
            if (c == pattern[0]) {
                cnt1++;
            }
        }
        // 在最前面或是最後面加上char之後的結果
        return res + max(cnt1, cnt2);
    }
};
