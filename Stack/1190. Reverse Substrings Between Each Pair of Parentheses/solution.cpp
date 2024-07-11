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
