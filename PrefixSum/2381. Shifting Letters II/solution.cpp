/*
 *   使用prefix sum把forward 和backward多少先計算出來
 *   最後再調整string
 *
 *   time  : O(M) , M : size of shifts, N : size of string s
 *   space : O(N)
 */
class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int sz = s.size();
        vector<int> pfs(sz + 1);
        for(const auto& s : shifts) {
            pfs[s[0]] += s[2] ? 1 : -1;
            pfs[s[1] + 1] += s[2] ? -1 : 1;
        }
        for(int i = 0, step = 0; i < sz; ++i) {
            step = (step + pfs[i]) % 26;
            if(step < 0) step += 26;
            s[i] = (s[i] - 'a' + step) % 26 + 'a';
        }
        return s;
    }
};
/*
            a, b, c
            |  |
[0, 1, 0]   z, a, c backward
               |  |
[1, 2, 1]   z, b, d forward

[0, 2, 1]   a, c, e forward

            -1    +1
               +1    -1
            +1       -1    
*/
