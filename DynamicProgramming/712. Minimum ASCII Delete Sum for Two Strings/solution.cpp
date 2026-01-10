/*  top-down recursive + memorization
 *
 *  time  : O(NM)
 *  space : O(NM)
 */
class Solution {
    int helper(string& s1, string& s2, int i, int j) {
        if(~mem[i][j]) return mem[i][j];
        else if(s1[i] == s2[j]) return mem[i][j] = helper(s1, s2, i + 1, j + 1);
        else return mem[i][j] = min(helper(s1, s2, i + 1, j) + s1[i], 
                                    helper(s1, s2, i, j + 1) + s2[j]);
    }
    // f(i, j) = f(i + 1, j + 1), f(i, j + 1), f(i + 1, j)
    vector<vector<int>> mem;
public:
    int minimumDeleteSum(string s1, string s2) {
        mem.resize(s1.size() + 1, vector<int>(s2.size() + 1, -1));
        mem.back().back() = 0;
        for(int i = s1.size() - 1, sum = 0; i >= 0; --i) {
            sum += s1[i];
            mem[i].back() = sum;
        }
        for(int i = s2.size() - 1, sum = 0; i >= 0; --i) {
            sum += s2[i];
            mem.back()[i] = sum;
        }
        return helper(s1, s2, 0, 0);
    }
};
/*  bottom-up tabulation
 * 
 *  time  : O(NM)
 *  space : O(NM)
 */
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1));
        for(int i = s1.size() - 1, sum = 0; i >= 0; --i) {
            sum += s1[i];
            dp[i].back() = sum;
        }
        for(int i = s2.size() - 1, sum = 0; i >= 0; --i) {
            sum += s2[i];
            dp.back()[i] = sum;
        }
        
        for(int i = s1.size() - 1; i >= 0; --i)
            for(int j = s2.size() - 1; j >= 0; --j) {
                if(s1[i] == s2[j]) dp[i][j] = dp[i + 1][j + 1];
                else dp[i][j] = min({dp[i + 1][j] + s1[i], dp[i][j + 1] + s2[j]});
            }
        return dp[0][0];
    }
};
