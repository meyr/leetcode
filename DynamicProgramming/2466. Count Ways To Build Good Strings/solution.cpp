/* top-down recursive + memozization
 *
 *  time  : O(N), N = high
 *  space : O(N)
 *
 */
class Solution {
    int mod = 1e9 + 7;
    int low, high, zero, one;
    int helper(int len) {
        if(len > high) return 0;
        else if(~mem[len]) return mem[len];
        else {
            int rtn = len >= low;
            return mem[len] = (rtn + helper(len + zero) + helper(len + one)) % mod;
        }
    }
    vector<int> mem;
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        this->low = low;
        this->high = high;
        this->zero = zero;
        this->one = one;
        mem.resize(high + 1, -1);
        return helper(0);
    }
};
/*  從上可知 helper(i) = (helper(i + one) + helper(i + zero) + (i >= low)) % mod;
 *  
 *  button-up tabulation
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    int mod = 1e9 + 7;
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        int rtn{};
        vector<int> dp(high + 1);
        for(int i = high; i >= 0; --i) {
            dp[i] = ((i + zero <= high ? dp[i + zero] : 0) +
                     (i + one <= high ? dp[i + one] : 0) +
                     (i >= low)) % mod;
        }
        return dp[0];
    }
};
