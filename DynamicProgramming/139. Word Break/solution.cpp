/*
 * time  : O(NM)
 * space : O(N + M)
 */
class Solution {
    unordered_set<string> us;
    int helper(string& s, int idx) {
        if(~mem[idx]) return mem[idx];
        for(auto& w : us) {
            int len = min(w.size(), s.size() - idx);
            string sub = s.substr(idx, len);
            if(sub == w && helper(s, idx + len))
                return mem[idx] = true; 
        }
        return mem[idx] = false;
    }
    vector<int> mem;
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        for(auto& word : wordDict) us.insert(word);
        mem.resize(s.size() + 1, -1);
        mem.back() = 1;
        return helper(s, 0);
    }
};
