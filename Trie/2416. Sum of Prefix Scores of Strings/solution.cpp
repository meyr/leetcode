/*
 * 使用Trie來記錄有多少個string
 * 之後就可以累加
 *
 *  ex: ["abc","ab","bc","b"]
 *
 *  a, b, c
 *  2  2  1
 *
 *  b, c
 *  2, 1
 *
 *  time  : O(N) , N total chars in words
 *  space : O(N)
 */
class Trie {
    struct node{
        unordered_map<char, node *> m;
        int cnt;
    };
    node *root;
    void addWord(string& word) {
        node *p = root;
        for(auto& c : word) {
            if(!p->m.count(c)) p->m[c] = new node();
            p->m[c]->cnt++;
            p = p->m[c];
        }
    }
public:
    Trie(vector<string>& words) {
        root = new node();
        for(auto& word : words) {
            addWord(word);
        }
    }
    int getScore(string& word) {
        int ans{};
        node *p = root;
        for(auto& c : word) {
            if(!p->m.count(c)) break;
            ans += p->m[c]->cnt;
            p = p->m[c];
        }
        return ans;
    }
};
class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        Trie trie(words);
        vector<int> ans;
        for(auto& word : words)
            ans.push_back(trie.getScore(word));
        return ans;
    }
};
/*
*/
