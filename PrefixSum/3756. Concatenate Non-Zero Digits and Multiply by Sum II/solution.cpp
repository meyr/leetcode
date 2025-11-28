/* ref : https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-ii/solutions/7368397/fully-explained-code-by-c_prateek-kfsj/
 * 不過我之前的想法和他類似 也是使用prefix sum來分別計算sum和x
 *
 * s   =    1, 0,  2,  0,  3,    0,   0,    4, 
 * pfs = 0, 1, 1,  3,  3,  6,    6,   6,   10, 
 * val = 0, 1, 1, 12, 12, 123, 123, 123, 1234, 
 * cnt = 0, 1, 1,  2,  2,  3,    3,   3,    4, 
 *
 * time  : O(N + Q)
 * space : O(N)
 */
class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int sz = s.size(), mod = 1e9 + 7;
        vector<int> pfs(sz + 1), val(sz + 1), cnt(sz + 1), pow10(sz + 1); // __important__ prefix sum使用size = sz + 1可以避免判斷非0情況
        pow10[0] = 1;
        for(int i = 1; i <= sz; ++i) {
            pfs[i] = pfs[i - 1] + (s[i - 1] - '0');
            if(s[i - 1] != '0') {
                val[i] = ((long long)val[i - 1] * 10 + (s[i - 1] - '0')) % mod;
                cnt[i] = cnt[i - 1] + 1;
            } else {
                val[i] = val[i - 1];
                cnt[i] = cnt[i - 1];
            }
            pow10[i] = ((long long)pow10[i - 1] * 10) % mod; // 計算pow10 所有可能的值
        }
        vector<int> ans;
        for(auto& q : queries) {
            int left = q[0], right = q[1] + 1;
            int sum = pfs[right] - pfs[left];
            int d = cnt[right] - cnt[left]; // 計算left和right兩個數之間相差多少個0
            long long x = (((val[right] - ((long long)val[left] * pow10[d]) % mod) % mod) + mod ) % mod; // 避免有負值所以多做 (x + mod) % mod
            ans.push_back((sum * x) % mod);
        }
        return ans;
    }
};
