/*
 * 
 *  time  : O(N^2) 不是很好 但系統有接受
 *  space : O(26*N) = O(N)
 */
class Solution {
public:
    int maximumLength(string s) {
        int maxlen{-1};
        vector<vector<int>> m(26, vector<int>(s.size() + 1));
        m[s[0] - 'a'][1]++;
        int prev = 0;
        for(int i = 1; i < s.size(); ++i) {
            if(s[prev] == s[i]) {
                for(int len = i - prev + 1; len >= max(maxlen, 1); --len) // ___只要找到max(maxlen, 1)即可___
                    if(++m[s[i] - 'a'][len] >= 3) maxlen = max(maxlen, len);
            } else {
                prev = i;
                if(++m[s[i] - 'a'][1] >= 3) maxlen = max(maxlen, 1);
            }
        }
        return maxlen;
    }
};
