/*
 *  分割字串到所有可能的結果
 *
 */
class Solution {
    bool check(string& str) {
        if(str.size() > 1 && str[0] == '0') return false;
        int val = stoi(str);
        if(val > 255) return false;
        else return true;
    }
public:
    vector<string> restoreIpAddresses(string s) {
        int sz = s.size();
        vector<string> rtn;
        for(int len1 = 1; len1 <= 3; ++len1)
            for(int len2 = 1; len2 <= 3; ++len2)
                for(int len3 = 1; len3 <= 3; ++len3) {
                    int total = len1 + len2 + len3;
                    if(sz - total > 3 || sz - total <= 0) continue;
                    int len4 = sz - len1 - len2 - len3;
                    string sub1 = s.substr(0, len1);
                    string sub2 = s.substr(len1, len2);
                    string sub3 = s.substr(len1 + len2, len3);
                    string sub4 = s.substr(len1 + len2 + len3);
                    if(check(sub1) && check(sub2) && check(sub3) && check(sub4)) {
                            rtn.push_back(sub1 + "." + sub2 + "." + sub3 + "." + sub4);
                       }
                }
        return rtn;
    }
};
