/*  參考解答: https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/solutions/3801837/recursive-memoization-by-yadivyanshu-by7b/
 *
 *  0/1 backpack的問題 選與不選
 *
 *  time  : O(N^2)
 *  space : O(N^2)
 *
 */
class Solution {
    int x, mod = 1e9 + 7;
    int helper(int n, int num) {
        if(n == 0) return 1;
        else if(n < 0 || pow(num, x) > n) return 0;
        else if(~mem[n][num]) return mem[n][num];
        else {
            int pick = helper(n - pow(num, x), num + 1);
            int skip = helper(n, num + 1);
            return mem[n][num] = (pick + skip) % mod;
        }
    }
public:
    vector<vector<int>> mem;
    int numberOfWays(int n, int x) {
        this->x = x;
        mem.resize(301, vector<int>(301, -1));
        return helper(n, 1);
    }
};
