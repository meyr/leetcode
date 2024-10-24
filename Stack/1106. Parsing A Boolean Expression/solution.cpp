/*  參考 : https://leetcode.com/problems/parsing-a-boolean-expression/solutions/5939345/beats-100-optimized-solution-python-java-c-o-n-o-n/
 *
 *  time  : O(N) 每個char都會處理一次
 *  space : O(N) 
 */

class Solution {
public:
    bool parseBoolExpr(string expression) {
        stack<char> st;

        for (char c : expression) {
            if (c == ',' || c == '(')   // 這些符號不影響操作
                continue;
            if (c == 't' || c == 'f' || c == '!' || c == '&' || c == '|') { // 把val和operation存起來
                st.push(c);
            }
            else if (c == ')') { // 因為每個操作 !(..) &(..) |(..) 都一定會有左右括弧 
                                 // 把右括弧視為一個完整的操作直到遇到'!','&','|'這三個操作符號
                                 //
                bool hasTrue = false, hasFalse = false; // AND 或是 OR 操作只在乎有沒有true或是有沒有false, AND --> 只在乎有沒有false
                                                        //                                                  OR  --> 只在乎有沒有true
                while (st.top() != '!' && st.top() != '&' && st.top() != '|') {
                    char val = st.top(); st.pop();
                    if (val == 't') hasTrue = true;
                    if (val == 'f') hasFalse = true;
                }
                char op = st.top(); st.pop();
                if (op == '!') {
                    st.push(hasTrue ? 'f' : 't');
                } else if (op == '&') {
                    st.push(hasFalse ? 'f' : 't');
                } else {
                    st.push(hasTrue ? 't' : 'f');
                }
            }
        }
        return st.top() == 't';
    }
};
