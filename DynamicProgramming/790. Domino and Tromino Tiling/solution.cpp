/*  參考 : https://leetcode.com/problems/domino-and-tromino-tiling/solutions/1620975/cpython-simple-solution-w-images-explana-r1aw/
 *
 *
 */
class Solution {
    int n, m = 1e9 + 7;
    long helper(int i, bool prev) {
        if(i > n) return 0;
        else if(i == n) return !prev;  // 前面沒有空格才算一個解答
        else {
            if(prev) // 前面有空格
                //        可能插入 * *       或是    * *     *
                //                                   *     * *
                return helper(i + 1, true) + helper(i + 1, false);
            else// 前面沒有空格
                //     可以插入 *                * *                           *    or   * *
                //              *                * *                           * *       *
                return (helper(i + 1, false) + helper(i + 2, false) + 2 * helper(i + 2, true)) % m;
        }
    }
public:
    int numTilings(int n) {
        this->n = n;
        return helper(0, false);
    }
};
/*  改成有記憶的DP形式
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    int n, m = 1e9 + 7;
    int helper(int i, bool prev) {
        if(i > n) return 0;
        else if(~mem[i][prev]) return mem[i][prev];
        else {
            if(prev)
                return mem[i][prev] = (helper(i + 1, true) + (long long)helper(i + 1, false)) % m;
            else
                return mem[i][prev] = (helper(i + 1, false) + helper(i + 2, false) + 2 * (long long)helper(i + 2, true)) % m;
        }
    }
    vector<vector<int>> mem;
public:
    int numTilings(int n) {
        this->n = n;
        mem.resize(n + 1, vector<int>(2, -1));
        mem.back()[0] = 1;
        mem.back()[1] = 0;
        return helper(0, false);
    }
};
