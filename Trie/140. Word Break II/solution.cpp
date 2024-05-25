/*
    因為尋找每個word最有效率的方法是Trie

*/

class Solution {
    struct node{
        unordered_map<char, struct node *> m;
        bool isWord;
        string str;
    };
    struct node *root;
    vector<string> rtn;
    void addWord(string& word) {
        struct node *p = root;
        for(auto& c : word) {
            if(!p->m.count(c)) p->m[c] = new struct node();
            p = p->m[c];
        }
        p->isWord = true;
        p->str = word;
    }
    void search(string& s, vector<string>& ans, int idx, struct node *p) {
        if(idx == s.size()) {
            string tmp;
            int len{};
            for(auto& w : ans) {
                tmp += w + " ";
                len += w.size();
            }
            if(tmp.size() > 0)  // 避免沒有東西可以pop_back
                tmp.pop_back();
            if(len == s.size()) // 確保答案的程度有符合 s 的長度
                rtn.push_back(tmp);
        } else {
            if(!p->m.count(s[idx]) || !p) return;
            p = p->m[s[idx]];
            if(p->isWord) {
                ans.push_back(p->str);
                search(s, ans, idx + 1, root);  // __important__ 需要重頭開始找
                ans.pop_back();    
            }
            search(s, ans, idx + 1, p);
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        root = new struct node();
        for(auto& word : wordDict) addWord(word);
        vector<string> ans;
        search(s, ans, 0, root);
        return rtn;
    }
};
