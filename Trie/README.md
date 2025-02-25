# Leetcode刷題學習筆記 -- Trie
## Introduction
因為C++沒有內建trie的data struct，所以必須自己implement。

### 使用unordered_map來實作
```cpp
class trie{
    struct node{
        unordered_map<char, node *> m;
        bool isWord;
        string word;
    };
    node *root;
    void addWord(string& s) {
        node *p = root;
        for(auto& c : s) {
            if(!p->m.count(c))
                p->m[c] = new node();
            p = p->m[c];
        }
        p->isWord = true;
        p->word = s;
    } 
public:
    trie() {
        root = new node();
    }
    trie(vector<string>& words) : trie() {
        for(auto& w : words)
            addWord(w);
    }
};
```
使用上面的程式碼，增加一個字串"OATH"，可以得到以下的結構。其中紀錄這個字串的屬性的isWord和word是在下一個node中。參考[Word Search II](https://hackmd.io/QDEA_oTZTwOqDc35dWwOHw?both#212-Word-Search-II)

![](https://i.imgur.com/QArgddw.png)
