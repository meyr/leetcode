/*  參考 : 2116. Check if a Parentheses String Can Be Valid
 *  
 *  使用balance先檢查string是否正確 
 *  如果不正確balance < 0表示這個index必須移除 把index儲存起來  
 *  最後如果balance > 0 表示後面有'(' 必須移除
 *
 *  time  : O(N)
 *  space : O(1)
 */
 class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int bal{};
        vector<int> rm, left;
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == '(' || s[i] == ')') {
                bal += s[i] == '(' ? 1 : -1;
                if(s[i] == '(') left.push_back(i);
                if(bal < 0) {
                    rm.push_back(i);
                    bal = 0;
                }
            }
        }
        if(bal) {
            for(int i = left.size() - bal; i < left.size(); ++i)
                rm.push_back(left[i]);
        }
        string rtn;
        for(int i = 0, j = 0; i < s.size(); ++i) {
            if(j < rm.size() && i == rm[j]) ++j;
            else rtn.push_back(s[i]);
        }
        return rtn;
    }
};
