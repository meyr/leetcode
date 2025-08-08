/*  ref : https://leetcode.com/problems/soup-servings/solutions/121711/cjavapython-when-n-4800-just-return-1-by-wp7v/
 *
 *  1. 當 A < 25ml 我們還是需要一次操作 才可以倒光它 所以 (A+24)/25 表示需要多少次的操作
 *  2. 為什麼會有N > 4800的判斷?
 *     因為四種操作 其實是最B不公平的 因為沒有 (A - 0, B - 100)的情況
 *     所以當N越大 A先被倒光的機率就越高
 *     lee測試只要N大於4800 機率就接近1 - 1e5 所以就不用計算 直接return 1.0
 */
class Solution {
public:
    double memo[200][200];
    double soupServings(int N) {
        return N > 4800 ?  1.0 : f((N + 24) / 25, (N + 24) / 25);
    }
    double f(int a, int b) {
        if (a <= 0 && b <= 0) return 0.5;
        if (a <= 0) return 1;
        if (b <= 0) return 0;
        if (memo[a][b] > 0) return memo[a][b];
        return memo[a][b] = 0.25 * (f(a-4,b)+f(a-3,b-1)+f(a-2,b-2)+f(a-1,b-3));
    }
};
/*  之前的參考解答
 *
 */
class Solution {
public:
    double soupServings(int n) {
        int m = ceil(n / 25.0);
        unordered_map<int, unordered_map<int, double>> dp;
        function<double(int, int)> helper = [&](int i, int j) {
            if(i <= 0 and j <= 0) return 0.5;
            else if(i <= 0) return 1.0;
            else if(j <= 0) return 0.0;
            else if(dp[i].count(j)) return dp[i][j];
            else return dp[i][j] = (
                helper(i - 4, j) +
                helper(i - 3, j - 1) +
                helper(i - 2, j - 2) +
                helper(i - 1, j - 3)) / 4.0;

        };
        for(int k = 1; k <= m; ++k)                     // 這邊就是在計算 N大於多少就會趨近於1.0
            if(helper(k, k) > 1 - 1e-5) return 1.0;
        return helper(m, m);
    }
};
