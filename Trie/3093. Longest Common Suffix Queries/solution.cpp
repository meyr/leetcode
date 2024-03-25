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
