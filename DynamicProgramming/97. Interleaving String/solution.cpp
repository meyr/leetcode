/*
 * time  : O(NM)
 * space : O(NM)
 */
class Solution {
    bool helper(string_view s1, int i, string_view s2, int j, string_view s3) {
        int k = i + j;
        if(~mem[i][j]) return mem[i][j];
        if(s1[i] == s3[k] && helper(s1, i + 1, s2, j, s3)) return mem[i][j] = true;
        if(s2[j] == s3[k] && helper(s1, i, s2, j + 1, s3)) return mem[i][j] = true;
        return mem[i][j] = false;
    }
    vector<vector<int>> mem;
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        mem.resize(s3.size() + 1, vector<int>(s3.size() + 1, -1));
        for(int i = 0; i <= s3.size(); ++i)
            mem[i][s3.size() - i] = 1;
        return helper(s1, 0, s2, 0, s3);
    }
};
