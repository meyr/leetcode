/*  參考 : 2116. Check if a Parentheses String Can Be Valid 
 * 
 *  因為'*'可以表示empty所以省去檢查s.size()%2 == 0
 *  
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
    bool check_from_left(string& s) {
        int bal{}, wild{};
        for(int i  = 0; i < s.size() && bal + wild >= 0; ++i) {
            if(s[i] == '*') wild++;
            else bal += s[i] == '(' ? 1 : -1;
        }
        return wild >= abs(bal);
    }
    bool check_from_right(string& s) {
        int bal{}, wild{};
        for(int i  = s.size() - 1; i >= 0 && bal + wild >= 0; --i) {
            if(s[i] == '*') wild++;
            else bal += s[i] == ')' ? 1 : -1;
        }
        return wild >= abs(bal);
    }
public:
    bool checkValidString(string s) {
        return check_from_left(s) && check_from_right(s);
    }
};
