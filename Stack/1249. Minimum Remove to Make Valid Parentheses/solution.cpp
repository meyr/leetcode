/*  
 *   判斷valid parentheses最好的方法是使用stack
 *   
 *   time  : O(N)
 *   space : O(N)
 */

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        vector<int> st;
        for(int i = 0; i < s.size(); ++i) {
            if(!isalpha(s[i])) {
                if(s[i] == ')' && !st.empty() && s[st.back()] == '(') st.pop_back();
                else st.push_back(i);
            }
        }
        string ans{};
        for(int i = 0, j = 0; i < s.size(); ++i) {
            if(j < st.size() && st[j] == i) j++;
            else ans.push_back(s[i]);
        }
        return ans;
    }
};
