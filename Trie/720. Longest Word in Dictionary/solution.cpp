/*
 * 使用Trie來判斷
 *
 */
class Solution {
    struct node{
        unordered_map<char, node*> m;
        string str;
        bool isWord;
    };
    void search(node *p, string& rtn) {
        if(!p->isWord) return; 

        if(p->str.size() > rtn.size())
            rtn = p->str;
        else if(p->str.size() == rtn.size())
            rtn = min(rtn, p->str);
        
        for(auto& ref : p->m)
            search(ref.second, rtn);
    }
public:
    string longestWord(vector<string>& words) {
        node* root = new node();
        root->isWord = true;
        for(auto& w : words) {
            node* p = root;
            for(auto& c : w) {
                if(!p->m.count(c)) p->m[c] = new node();
                p = p->m[c];
            }
            p->isWord = true;
            p->str = w;
        }
        string rtn{};
        search(root, rtn);
        return rtn;
    }
};
