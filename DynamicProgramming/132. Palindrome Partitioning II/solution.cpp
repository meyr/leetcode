/*  使用DP solution
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    bool isPalindrome(string& s, int i, int j) {
        for(; i < j; ++i, --j)
            if(s[i] != s[j]) return false;
        return true;
    }
    int helper(string& s, int idx) {
        if(~mem[idx]) return mem[idx];
        int rtn = s.size();
        for(int j = idx; j < s.size(); ++j)
            if(isPalindrome(s, idx, j))
                rtn = min(rtn, helper(s, j + 1) + 1);
        return mem[idx] = rtn;
    }
    vector<int> mem;
public:
    int minCut(string s) {
        mem.resize(s.size() + 1, -1);
        mem.back() = 0;
        return helper(s, 0) - 1;
    }
};
