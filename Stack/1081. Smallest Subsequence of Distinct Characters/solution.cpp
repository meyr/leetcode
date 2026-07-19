/*  
 *  看了hint有monotonic stack才想到可以用stack
 *  因為要求要Lexicographically Smaller 所以我一個char已經在rtn內
 *  但是後面還有(um[rtn.back()] > 0) 且 要放入得比rtn.back()還小 就可以丟掉
 *  注意使用過的就不能再放進去 但是um[c]--; 因為 um表示的是後面的char還剩多少個。
 *
 *  time  : O(N)
 *  space : O(N)
 */

class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> um(26);
        for(const auto& c : s) um[c - 'a']++;
        string rtn{};
        bitset<26> used;
        for(const auto& c : s) {
            um[c - 'a']--;
            if(used.test(c - 'a')) continue;
            while(!rtn.empty() && c < rtn.back() && um[rtn.back() - 'a'] > 0) {
                used.reset(rtn.back() - 'a');
                rtn.pop_back();
            }
            rtn.push_back(c);
            used.set(c - 'a', 1);
        }
        return rtn;
    }
};
