/*   
 *   直覺使用Trie
 *   
 *   另外多儲存index來表示目前的最短string的index
 */

class Solution {
    vector<int> len;
    struct node{
        unordered_map<char, node*> m;
        int idx;
        node(int i) : idx(i){}
    };
    node* root;
    void addWord(string& w, int i) {
        node* p = root;
        if(len[p->idx] > len[i])
            p->idx = i;
        for(int j = w.size() - 1; j >= 0; --j) {
            if(!p->m.count(w[j]))
                p->m[w[j]] = new node(i);
            p = p->m[w[j]];
            if(len[p->idx] > len[i])
                 p->idx = i;
        }
    }
    int query(string& w) {
        node* p = root;
        for(int j = w.size() - 1; j >= 0; --j) {
            if(!p->m.count(w[j])) return p->idx;
            p = p->m[w[j]];
        }
        return p->idx;
    }
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        root = new node(0);
        for(int i = 0; i < wordsContainer.size(); ++i) {
            len.push_back(wordsContainer[i].size());
            addWord(wordsContainer[i], i);
        }
        
        vector<int> ans;
        for(auto& w : wordsQuery)
            ans.push_back(query(w));
        return ans;
    }
};
/* 2026/05/28 daily challenge
 *
 * 寫出類似上面的但是MLE
 * 因為是suffix所以反著建立Trie 同時記錄到此的word idx和word length(方便以後比較)
 *
 * 即使把unordered_map改成vector還是MLE
 *
 */
class Trie{
    struct node{
        unordered_map<char, node*> m;
        int idx; // index of smallest length
        int len;
        node() : idx(-1), len(INT_MAX) {}
    };
    node* root;
    void add(const string& word, int idx) {
        node* p = root;
        int sz = word.size();
        if(sz <= p->len) {
            p->len = sz;
            p->idx = idx;
        }
        for(int i = sz - 1; i >= 0; --i) {
            if(!p->m.count(word[i])) p->m[word[i]] = new node();
            p = p->m[word[i]];
            if(sz <= p->len) {
                p->len = sz;
                p->idx = idx;
            }
        }
    }
public:
    Trie(const vector<string>& words) {
        int sz = words.size();
        root = new node();
        for(int i = sz - 1; i >= 0; --i)
            add(words[i], i);
    }
    int find(const string& word) {
        node* p = root;
        int rtn = p->idx, sz = word.size();
        for(int i = sz - 1; p && i >= 0; --i) {
            if(!p->m.count(word[i]))
                break;
            else
                p = p->m[word[i]];
            rtn = p->idx;
        }
        return rtn;
    }

};
class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        Trie trie(wordsContainer);
        vector<int> rtn;
        for(const auto& q : wordsQuery)
            rtn.push_back(trie.find(q));
        return rtn;
    }
};
/*  改成shared_ptr可以不用處理release resoruce的問題這樣可以AC 但是time complexity不是很好
 */
class Trie{
    struct node{
        unordered_map<char, shared_ptr<node>> m;        // <-- 改儲存shared_ptr
        int idx; // index of smallest length
        int len;
        node() : idx(-1), len(INT_MAX) {}
    };
    shared_ptr<node> root;
    void add(const string& word, int idx) {
        auto p = root;
        int sz = word.size();
        if(sz <= p->len) {
            p->len = sz;
            p->idx = idx;
        }
        for(int i = sz - 1; i >= 0; --i) {
            if(!p->m.count(word[i])) p->m[word[i]] = make_shared<node>();   // 建立shared_ptr
            p = p->m[word[i]];
            if(sz <= p->len) {
                p->len = sz;
                p->idx = idx;
            }
        }
    }
public:
    Trie(const vector<string>& words) {
        int sz = words.size();
        root = make_shared<node>();
        for(int i = sz - 1; i >= 0; --i)
            add(words[i], i);
    }
    int find(const string& word) {
        auto p = root;
        int rtn = p->idx, sz = word.size();
        for(int i = sz - 1; p && i >= 0; --i) {
            if(!p->m.count(word[i]))
                break;
            else
                p = p->m[word[i]];
            rtn = p->idx;
        }
        return rtn;
    }

};
class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        Trie trie(wordsContainer);
        vector<int> rtn;
        for(const auto& q : wordsQuery)
            rtn.push_back(trie.find(q));
        return rtn;
    }
};
/*  參考gemini的解法
 *  因為leetcode 會不斷的跑testcase導致上面new的node不會被釋放 而且容易產生記憶體碎片
 *  使用vector<node> 產生的node只會在vector內 根據RAII 下一個testcase就會被釋放 而且vector會allocate一個連續記憶體 比較不會產生記憶體碎片化
 */
class Trie {
    struct Node {
        vector<int> child;  // 只記錄在tree內的index
        int idx;
        int len;
        Node() : child(26, 0), idx(-1), len(INT_MAX){}
    };

    vector<Node> tree;  // __important__ 使用vector來記錄新產生的node
    void add(string_view word, int idx) {
        int p = 0;
        int sz = word.size();
        if (sz <= tree[p].len) {    // 如果suffix完全不match也會有一個default index
            tree[p].len = sz;
            tree[p].idx = idx;
        }

        for (int i = sz - 1; i >= 0; --i) {
            int c = word[i] - 'a';
            if (tree[p].child[c] == 0) {
                tree[p].child[c] = tree.size(); // 先記錄index
                tree.emplace_back();            // 產生一個新的node
            }
            p = tree[p].child[c];
            if (sz <= tree[p].len) {
                tree[p].len = sz;
                tree[p].idx = idx;
            }
        }
    }

public:
    Trie(const vector<string>& words) {
        int sz = words.size();
        tree.emplace_back();                // __impoartant__ 必須要有一個root node
        for (int i = sz - 1; i >= 0; --i)
            add(words[i], i);
    }

    int find(string_view word) {
        int p = 0;
        int rtn = tree[p].idx;              // default index
        int sz = word.size();

        for (int i = sz - 1; i >= 0; --i) {
            int c = word[i] - 'a';
            if (tree[p].child[c] == 0) {    // 找不到下一個char
                break;
            }
            p = tree[p].child[c];
            rtn = tree[p].idx;
        }
        return rtn;
    }
};

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        Trie trie(wordsContainer);
        vector<int> rtn(wordsQuery.size());
        for (int i = 0; i < wordsQuery.size(); ++i)
            rtn[i] = trie.find(wordsQuery[i]);

        return rtn;
    }
};
