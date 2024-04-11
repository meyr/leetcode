/*
 *  使用stack來判斷目前的char是否可以刪除掉之前的char
 *
 *  time  : O(N)
 *  space : O(N)
 *
 */
class Solution {
public:
    string removeKdigits(string num, int k) {
        if(k == num.size()) return "0";
        string st;
        for(auto& c : num) {
            if(st.empty() || k == 0) st.push_back(c);
            else {
                while(k && !st.empty() && c < st.back()) {
                    st.pop_back();
                    k--;
                }
                st.push_back(c);
            }
        }
        while(!st.empty() && k) {
            st.pop_back();
            k--;
        }
        int i = 0;
        while(st[i] == '0') i++;
        string ans = st.substr(i);
        if(ans.empty()) return "0";
        else return ans;
    }
};
