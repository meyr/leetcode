/*
 *  time  : O(2N) = O(N)
 *  space : O(2N) = O(N)
 */
class Solution {
    long long helper(vector<int>& A, vector<int>& B, int sel, int idx) {
        if(idx >= A.size()) return 0;
        if(~mem[sel][idx]) return mem[sel][idx];
        long long drink = (sel ? B[idx] : A[idx]) + helper(A, B, sel, idx + 1);
        long long switchDrink = helper(A, B, !sel, idx + 1);
        return mem[sel][idx] = max(drink, switchDrink);
    }
    // f(0, idx) = f(A[idx] + f(0, idx + 1), f(1, idx + 1))
    // f(1, idx) = f(B[idx] + f(1, idx + 1), f(0, idx + 1))
    vector<vector<long long>> mem;
public:
    long long maxEnergyBoost(vector<int>& A, vector<int>& B) {
        mem.resize(2, vector<long long>(A.size(), -1));
        return max(helper(A, B, 0, 0),
                   helper(A, B, 1, 0));
    }
};
/*
 *  buttom-up, tabulation solution
 *  time  : O(N)
 *  sapce : O(N)
 */
class Solution {
public:
    long long maxEnergyBoost(vector<int>& A, vector<int>& B) {
        vector<vector<long long>> dp(2, vector<long long>(A.size() + 1));
        for(int i = A.size() - 1; i >= 0; --i) {
            dp[0][i] = max(A[i] + dp[0][i + 1], dp[1][i + 1]);
            dp[1][i] = max(B[i] + dp[1][i + 1], dp[0][i + 1]);
        }
        return max(dp[0][0], dp[1][0]);
    }
};
