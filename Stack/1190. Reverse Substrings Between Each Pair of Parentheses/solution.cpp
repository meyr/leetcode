/*
 *  使用stack 每遇到'('就加一層 每遇到')'就把最後一層內容顛倒
 *
 *  time  : O(N)
 *  space : O(N), N : size of s
 */

class Solution {
public:
    string reverseParentheses(string s) {
        st.push_back(vector<string>());
        st.back().push_back("");
        for(auto& c : s) {
            if(c == '(') {
                st.push_back(vector<string>());
                st.back().push_back("");
            }
            else if(c == ')') {
                string tmp;
                int sz = st.back().size();
                for(int i = sz - 1; i >= 0; --i) {
                    string& str = st.back()[i];
                    reverse(str.begin(), str.end());
                    tmp = tmp + str;
                    st.back().pop_back();
                }
                st.pop_back();
                st.back().push_back(tmp);
            } else st.back().back().push_back(c);
        }
        string ans{};
        for(auto& s : st.front())
            ans = ans + s;
        return ans;
    }
};
/*
 *  參考解答 : https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/solutions/382422/0-ms-stack-solution-c/
 *
 *  和上面的類似 其實我們在乎的只是'(' 和 ')' 的位置 所以使用stack來儲存遇到的'('
 *  遇到')'就把這中間的string反轉
 *  最後拿掉所有的'('和')'
 *
 */
class Solution {
public:
    string reverseParentheses(string s) {
        stack<int> st;
        string res;
        for (int i = 0; i < s.size(); i ++) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                int top = st.top();
                st.pop();
                reverse(s.begin() + top + 1, s.begin() + i);
            }
        }
        for (auto it: s) {
            if (it != '(' && it != ')') {
                res.push_back(it);
            }
        }
        return res;
    }
};
