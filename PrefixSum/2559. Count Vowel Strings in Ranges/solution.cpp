/*  題目的重點是判斷第一個和最後一個都是母音 才是vowel string
 *
 *  time  : O(N)
 *  space : O(N)
 *
 */
class Solution {
    unordered_set<char> vowel{{'a'}, {'e'}, {'i'}, {'o'}, {'u'}};
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        int sz = words.size();
        vector<int> pfs(sz + 1);
        auto is_vowel = [&](string& str) -> bool {
            return vowel.count(str.front()) && vowel.count(str.back());
        };
        for(int i = 0; i < sz; ++i) 
            pfs[i + 1] = pfs[i] + is_vowel(words[i]);
        vector<int> ans;
        for(const auto& q : queries)
            ans.push_back(pfs[q[1] + 1] - pfs[q[0]]);
        return ans;
    }
};
