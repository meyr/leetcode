/*
 *    一開始的想法是有三種情況 n - 1, n % 2 == 0 ? f(n/2), n % 3 == 0 ? f(n/3)
 *    之後再用memorization的方法加速，但是這樣會TLE
 *    因為n - 1這個等於是全部的情況都遍歷一次
 *    而且1 <= n <= 2 * 1e9，如果是n == 2*1e9 也會MLE，使用vector<int> mem(n + 1)的方法也不好
 */

class Solution {
    int helper(int n) {
        if(~mem[n]) return mem[n];
        else {
            int rtn = minDays(n - 1);
            if(n % 2 == 0) rtn = min(rtn, minDays(n / 2));
            if(n % 3 == 0) rtn = min(rtn, minDays(n / 3));
            return mem[n] = rtn + 1;
        }
    }
    vector<int> mem;
public:
    int minDays(int n) {
        if(n == 1) return 1;
        else if(n <= 3) return 2;
        mem.resize(n + 1, -1);
        mem[1] = 1;
        mem[2] = mem[3] = 2;
        return helper(n);
    }
};
/*
    10 -> (9, 5)  day 1
    9->(8, 3) day2
    3->(2, 1) day3

*/
