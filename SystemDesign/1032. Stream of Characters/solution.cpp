/*
 *  使用trie紀錄words, 使用一組pointer來記錄目前的suffix到哪裡了 
 *
 */
class StreamChecker {
    struct node{
        unordered_map<char, struct node*> m;
        bool isWord;
    };
    struct node *root;
    void add(const string& word) {
        struct node *p = root;
        for(const auto& c : word) {
            if(!p->m.count(c))
                p->m[c] = new struct node();
            p = p->m[c];
        }
        p->isWord = true;
    }
    queue<struct node*> lists;
public:
    StreamChecker(vector<string>& words) {
        root = new struct node();
        for(const auto& word : words)
            add(word);
    }
    
    bool query(char letter) {
        bool rtn{false};
        for(int loop = lists.size(); loop > 0; --loop) {
            struct node *p = lists.front(); lists.pop();
            if(p->m.count(letter)) {
                p = p->m[letter];
                rtn |= p->isWord;
                lists.push(p);
            }
        }
        if(root->m.count(letter)) {
            rtn |= root->m[letter]->isWord;
            lists.push(root->m[letter]);
        }
        return rtn;
    }
};
