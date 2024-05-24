/*
 *  因為words.length <= 14 所以可以使用Backtracking
 *
 */

class Solution {
    vector<int> count;
    void addVector(vector<int>& a, vector<int>& b) {
        for(int i = 0; i < b.size(); ++i)
            a[i] += b[i];
    }
    void subVector(vector<int>& a, vector<int>& b) {
        for(int i = 0; i < b.size(); ++i)
            a[i] -= b[i];        
    }
    bool couldTake(vector<int>& st) {
        for(int i = 0; i < st.size(); ++i)
            if(count[i] < st[i]) return false;
        return true;
    }
    int helper(vector<string>& words, vector<int>& score, int idx) {
        if(idx == words.size()) return 0;
        vector<int> st(26);
        int sc{};
        for(auto& c : words[idx]) {
            st[c - 'a']++;
            sc += score[c - 'a'];
        }
        int take{};
        if(couldTake(st)) {
            subVector(count, st);
            take = sc + helper(words, score, idx + 1);
            addVector(count, st);
        }
        int notake = helper(words, score, idx + 1);
        return max(take, notake);
    }
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        count.resize(26);
        for(auto& c : letters) count[c - 'a']++;
        return helper(words, score, 0);
    }
};
