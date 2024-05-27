/*  這題想了很久不知道怎麼下手 所以從brust-force開始解 
 *  而且他的constraints為 1 <= pattern.length, s.length <= 20
 *  所以使用backtracking
 *
 *  很簡單的想法就是假設去試每個pattern的所有長度的可能
 *
 */
class Solution {
    unordered_map<char, string> m;
    unordered_map<string, char> s2c; // 一種character只能對應一個string 所以建立map來反查
    bool helper(string& p, int i, string& s, int j) {
        if(i == p.size() && j == s.size()) return true;
        else if(i == p.size() || j == s.size()) return false;
        else if(!m.count(p[i])) {
            for(int len = 1; len <= s.size() - j; ++len) {
                string sub = s.substr(j, len);
                if(s2c.count(sub)) continue; // 檢查是否有重複
                m[p[i]] = sub;
                s2c[sub] = p[i];
                if(helper(p, i + 1, s, j + len))    // 如果有一種case成立就可以一直離開不用再試 
                    return true;
                s2c.erase(sub);
            }
            m.erase(p[i]);
        } else {
            if(s.size() - j < m[p[i]].size()) return false;
            if(s.substr(j, m[p[i]].size()) == m[p[i]])
                if(helper(p, i + 1, s, j + m[p[i]].size())) // 如果有一種case成立就可以一直離開不用再試 
                    return true;
            
        }
        return false;
    }
public:
    bool wordPatternMatch(string pattern, string s) {
        if(pattern.size() == 1) return true;
        return helper(pattern, 0, s, 0);
    }
};
