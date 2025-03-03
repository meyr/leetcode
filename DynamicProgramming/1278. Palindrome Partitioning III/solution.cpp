/*  類似 131 和 132的作法 使用暴力破解 就是把所有的可能都列舉出來
 *
 *   因為k是可以分成的group 所以列舉所有的可能
 *    a, b, c     k = 2
 * 
 *    a, bc   --> 1
 *    ab, c   --> 1
 * 
 *    aabbc, k = 3
 *    a, a, bbc   --> 1
 *    a, ab, bc   --> 2
 *    a, abb, c   --> 1
 *    aa, b, bc   --> 1
 *    aa, bb, c   --> 0
 *    aab, b, c   --> 1
 *
 *    結果TLE
 */
class Solution {
    int calculate(string& s, vector<pair<int, int>>& strs) {
        int rtn{};
        for(auto& str : strs) {
            int i = str.first, j = str.second;
            for(; i < j; ++i, --j)
                rtn += s[i] != s[j];
        }
        return rtn;
    }
    int rtn;
    void helper(string& s, vector<pair<int, int>>& ans, int k, int idx) {
        if(k == 1) {
            ans.push_back({idx, s.size() - 1});
            rtn = min(rtn, calculate(s, ans));
            ans.pop_back();
        } else {
            for(int len = 1; len <= s.size() - idx - k + 1; ++len) {
                ans.push_back({idx, idx + len - 1});
                helper(s, ans, k - 1, idx + len);
                ans.pop_back();
            }
        }
    }
public:
    int palindromePartition(string s, int k) {
        rtn = s.size();
        vector<pair<int, int>> ans{};
        helper(s, ans, k, 0);
        return rtn;
    }
};
/*  意識到這個問題可以用DP 甚至不用儲存vector<string> ans
 *  所以修正成以下的code
 *
 *  time  : O(KN)
 *  space : O(KN)
 */
class Solution {
    int calculate(const string& s, int i, int j) {
        int rtn{};
        for(; i < j; ++i, --j)
            rtn += s[i] != s[j];
        return rtn;
    }
    int helper(string& s, int k, int idx) {
        if(~mem[k][idx]) return mem[k][idx];
        else if(k == 1)
            return mem[k][idx] = calculate(s, idx, s.size() - 1);
        else {
            int rtn = s.size();
            for(int len = 1; len <= s.size() - idx - k + 1; ++len)
                rtn = min(rtn, helper(s, k - 1, idx + len) +  calculate(s, idx, idx + len - 1));
            return mem[k][idx] = rtn;
        }

    }
    vector<vector<int>> mem;
public:
    int palindromePartition(string s, int k) {
        mem.resize(k + 1, vector<int>(s.size(), -1));
        return helper(s, k, 0);
    }
};
