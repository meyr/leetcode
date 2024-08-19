/*  因為操作只有copy all, paste
 *  所以給個狀態下只有 copy all and paste, paste only
 *  跳過 n == 1的情況 且第一次一定要copy and paste
 *
 *  time  : O(N^2)
 *  space : O(N^2)
 */
class Solution {
    int target;
    int helper(int sz, int cp) {
        if(sz == target) return 0;
        int copyAndPast = sz * 2 <= target ? helper(sz * 2, sz) + 2 : 1e3+1;
        int pastOnly = sz + cp <= target ? helper(sz + cp, cp) + 1 : 1e3 + 1;
        return min(copyAndPast, pastOnly);
    }
public:
    int minSteps(int n) {
        if(n == 1) return 0;
        target = n;
        return helper(2, 1) + 2;
    }
};
/*
 *  參考解答 : https://leetcode.cn/problems/2-keys-keyboard/solutions/1004937/zhi-you-liang-ge-jian-de-jian-pan-by-lee-ussa/
 *  
 *  最終答案是n, 所以最後一次paste, 為n - j, f[n - j] + 1
 *  因為copy and paste需要兩次操作 所以最好是達到n 的因數速之後一直paste
 *  
 *  time  : O(N * sqrt(N))
 *  space : O(N)
 */

class Solution {
public:
    int minSteps(int n) {
        vector<int> f(n + 1);
        for(int i = 2; i <= n; ++i) {
            f[i] = INT_MAX;
            for(int j = 1; j * j <= i; ++j) {
                if(i % j == 0) {// i = 100, j = 20, f[20] + 5
                                //                  f[5] + 20
                    f[i] = min(f[i], f[j] + i / j);
                    f[i] = min(f[i], f[i / j] + j);
                }
            }
        }
        return f.back();
    }
};
