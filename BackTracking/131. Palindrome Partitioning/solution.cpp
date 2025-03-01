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
/*
 *  2025/03/01 daily challenge
 *  一開始真的把substring切出來 太讓廢時間了, 後來使用isPalindrome(s, idx, len)
 *  解法一樣只是判斷isPalindrome不太一樣
 */
 class Solution {
    vector<vector<string>> rtn;
    bool isPalindrome(const string& str, int idx, int len) {
        int i = idx, j = idx + len - 1;
        while(i < j && str[i] == str[j])
            i++, j--;
        return i >= j;
    }
    void helper(string& s, int idx, vector<string>& ans) {
        if(idx == s.size()) rtn.push_back(ans);
        else {
            for(int len = 1; len <= s.size() - idx; ++len) {
                if(isPalindrome(s, idx, len)) {
                    ans.push_back(s.substr(idx, len));
                    helper(s, idx + len, ans);
                    ans.pop_back();
                }
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        vector<string> ans{};
        helper(s, 0, ans);
        return rtn;
    }
};
