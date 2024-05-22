/*
 *  因為要求每個答案都要是palindrome 
 *  所以找到palindrome才需要push進去
 *
 */

class Solution {
    vector<vector<string>> rtn;
    bool isPalindrome(string& s, int i, int j) {
        while(i < j) {
            if(s[i++] != s[j--]) 
                return false;
        }
        return true;
    }
    void helper(string& s, vector<string>& ans, int idx) {
        if(idx == s.size())
            rtn.push_back(ans);
        else {
            for(int i = idx; i < s.size(); ++i) { // 找到palindrome才需要push進去
                if(isPalindrome(s, idx, i)) {
                    ans.push_back(s.substr(idx, i - idx + 1));
                    helper(s, ans, i + 1);
                    ans.pop_back();
                }
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        vector<string> ans;
        helper(s, ans, 0);
        return rtn;
    }
};
