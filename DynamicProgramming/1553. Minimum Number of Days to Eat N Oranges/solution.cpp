/*
 *   參考解答: https://leetcode.com/problems/minimum-number-of-days-to-eat-n-oranges/solutions/794162/c-java-python-5-lines/
 *   
 *   因為 n % 2 == 0 或是 n % 3 == 0 也就是說只要吃掉一個或是兩個(n%2 or n%3)就可以進行大跳躍。
 *   題目的吃掉一個就是讓你把數值從 n 變成可以被2或3整除的數。
 *   例如: 10 -> 10%2 = 0, 10%3=1
 *    
 *   使用unordered_map也可以避免MLE 只記錄需要的element不用全部都allocate
 *   time  : O(N)
 *   space : O(N)
 */

class Solution {
    unordered_map<int, int> dp{{0, 0}, {1, 1}};
public:
    int minDays(int n) {
        if(!dp.count(n))
            dp[n] = 1 + min(n % 2 + minDays(n / 2), n % 3 + minDays(n / 3));
                 //^^^^  n = 2, dp[2] = 1 + min(0+minDays(1), 2 + minDays(0))
                 //                     1 + min(     1      , 2 + 0) = 2
                 //
                 //      n = 3, dp[3] = 1 + min(1 + minDays(1), 0 + minDays(1))
                 //                     1 + min(1 + 1         , 0 + 1) = 1 + 1 = 2
                 //                     ^^ 對n%2來說是 n - 1
                 //                        對n%3來說是一次扣掉2*n/3
        return dp[n];
    }
};
