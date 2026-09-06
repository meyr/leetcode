/*
 *   time  : O(NM)
 *   space : O(NM)
 *
 */
class Solution {
    int helper(string_view s, string_view t, int i, int j) {
        if(~mem[i][j]) return mem[i][j];
        else return mem[i][j] = helper(s, t, i + 1, j) + 
                (s[i] == t[j] ? helper(s, t, i + 1, j + 1) : 0);
    }
    vector<vector<int>> mem;
public:
    int numDistinct(string s, string t) {
        mem.resize(s.size() + 1, vector<int>(t.size() + 1, -1));
        for(int j = 0; j <= t.size(); ++j) mem[s.size()][j] = 0;
        for(int i = 0; i <= s.size(); ++i) mem[i][t.size()] = 1;
        return helper(s, t, 0, 0);
    }
};
