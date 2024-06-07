/*
 *  很直覺的使用Trie
 *
 */

class Trie{
    struct node{
        unordered_map<char, struct node *> m;
        bool isWord;
        int idx;
    };
    struct node *root;
public:
    Trie(vector<string>& words) {
        root = new struct node();
        for(int i = 0; i < words.size(); ++i)
            addWord(words[i], i);
    }

    void addWord(string& word, int idx = -1) {
        struct node *p = root;
        for(auto& c : word) {
            if(!p->m.count(c))
                p->m[c] = new struct node();
            p = p->m[c];
        }
        p->isWord = true;
        p->idx = idx;
    }

    int search(string& word) {
        struct node *p = root;
        for(auto& c : word) {
            if(!p->m.count(c)) return -1;
            p = p->m[c];
            if(p->isWord) return p->idx;
        }
        return -1;
    }
};
class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        Trie trie(dictionary);
        string rtn{};
        istringstream iss(sentence);
        string word;
        while(iss >> word) {
            int idx = trie.search(word);
            if(idx == -1) rtn += word;
            else rtn += dictionary[idx];
            rtn += " ";
        }
        rtn.pop_back();
        return rtn;
    }
};
