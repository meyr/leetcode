/*
 *   使用rolling hash來判斷string是否相同
 *
 *   time  : O(N)
 *   space : O(N)
 */

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<char, int> val{{'A', 1}, {'C', 2}, {'T', 3}, {'G', 4}};
        unordered_map<long long, int> m; //hash value, count
        vector<string> ans;
        int mod = 1e9 + 7, p = 31;
        long long hash{}, pk = 1;
        for(int i = s.size() - 1; i >= 0; --i) {
            hash = (hash * p + val[s[i]]) % mod;
            if(i + 10 >= s.size()) 
                pk = pk * p % mod;
            else
                hash = (hash - val[s[i + 10]] * pk % mod + mod) % mod;
            if(m[hash]++ == 1) ans.push_back(s.substr(i, 10));
        }
        return ans;
    }
};
