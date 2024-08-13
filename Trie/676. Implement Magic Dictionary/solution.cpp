class MagicDictionary {
    struct node{
        unordered_map<char, node*> m;
        bool isWord;
    };
    node* root;
    bool search(string searchWord, node* p, int cnt, int idx) {
        if(cnt == 2 || p == nullptr) return false;
        else if(idx == searchWord.size()) return cnt == 1 && p->isWord; // 檢查一定要換一個char 並且是一個完整的word
        
        char& c = searchWord[idx];
        for(auto& ref : p->m) // 總是檢查每個char
            if(search(searchWord, ref.second, cnt + (ref.first != c), idx + 1)) 
                return true;
            
        return false;
    }
public:
    MagicDictionary() {
        root = new node();
    }
    
    void buildDict(vector<string> dictionary) {
        for(auto& word : dictionary) {
            node* p = root;
            for(auto& c : word) {
                if(!p->m.count(c)) p->m[c] = new node();
                p = p->m[c];
            }
            p->isWord = true;
        }
    }
    
    bool search(string searchWord) {
        return search(searchWord, root, 0, 0);
    }
};
