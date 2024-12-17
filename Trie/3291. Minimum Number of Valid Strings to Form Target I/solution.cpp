/*  使用Trie 和 DP 來解 結果TLE
 *
 */
class Trie{
    struct node{
        unordered_map<char, struct node*> m;
    };
    struct node* root;
    void add(string& word) {
        struct node *p = root;
        for(auto& c : word) {
            if(!p->m.count(c))
                p->m[c] = new struct node();
            p = p->m[c];
        }
    }
public:
    Trie(vector<string>& words) {
        root = new struct node();
        for(auto& word : words)
            add(word);
    }
    bool find(string& str) {
        struct node *p = root;
        for(auto& c : str) {
            if(p->m.count(c)) p = p->m[c];
            else return false;
        }
        return true;
    }
};
class Solution {
    
    int helper(Trie& trie, string& target, int idx) {
        //if(idx == target.size()) return 0;
        if(~mem[idx]) return mem[idx];
        int ans = 1e6;
        for(int len = 1; len + idx <= target.size(); ++len) {
            string sub = target.substr(idx, len); // 因為find每次都會重頭開始找 效率不好
            if(trie.find(sub)) ans = min(ans, 1 + helper(trie, target, idx + len));
            else break;
        }
        return mem[idx] = ans;
    }
    vector<int> mem;
public:
    int minValidStrings(vector<string>& words, string target) {
        Trie trie(words);
        mem.resize(target.size() + 1, -1);
        mem.back() = 0;
        int ans =  helper(trie, target, 0);
        return ans >= 1e6 ? -1 : ans;
    }
};
/*  參考解答 : https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-i/solutions/5788470/dp-bhi-lagega-trie-bhi-lagega-aaiye-bc-d-iykg/
 *
 */
class TrieNode {
public:
    TrieNode* childs[26];
    TrieNode() {
        for (int i = 0; i < 26; ++i) {
            childs[i] = nullptr;
        }
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* temp = root;
        for (char c : word) {
            int idx = c - 'a';
            if (temp->childs[idx] == nullptr) {
                temp->childs[idx] = new TrieNode();
            }
            temp = temp->childs[idx];
        }
    }
};

class Solution {
public:
    int n;
    string target;
    vector<int> dp;

    int solve(int i, TrieNode* root) {
        if (i == n) return 0;
        if (dp[i] != -1) return dp[i];

        TrieNode* temp = root;
        int res = INT_MAX;

        for (int j = i; j < n; ++j) {
            int idx = target[j] - 'a';
            if (temp->childs[idx] == nullptr) break;
            temp = temp->childs[idx]; // __important__ 因為match了 下一次繼續從temp開始找 不要重頭找
            int t = solve(j + 1, root);
            if (t != INT_MAX) {
                res = min(res, t + 1);
            }
        }
        return dp[i] = res;
    }

    int minValidStrings(vector<string>& words, string target) {
        Trie trie;
        for (string word : words) {
            trie.insert(word);
        }
        n = target.size();
        this->target = target;
        dp = vector<int>(n, -1);

        int res = solve(0, trie.root);
        return res == INT_MAX ? -1 : res;
    }
};
/*  根據上面參考解答修正了第一個答案
 *
 */
struct node{
    unordered_map<char, struct node*> m;
};

class Trie{
    struct node* root;
    void add(string& word) {
        struct node *p = root;
        for(auto& c : word) {
            if(!p->m.count(c))
                p->m[c] = new struct node();
            p = p->m[c];
        }
    }
public:
    Trie(vector<string>& words) {
        root = new struct node();
        for(auto& word : words)
            add(word);
    }
    node* getRoot() {
        return root;
    }
};
class Solution {
    string target;
    node *root;
    int helper(node* p, int idx) {
        if(~mem[idx]) return mem[idx];
        int ans = 1e6;
        struct node *tmp = root;
        for(int j = idx; j < target.size(); ++j) {
            if(tmp->m.count(target[j])) {
                tmp = tmp->m[target[j]];    // __important__ 繼續找下一個
                ans = min(ans, 1 + helper(root, j + 1));
            } else break;
        }
        return mem[idx] = ans;
    }
    vector<int> mem;
public:
    int minValidStrings(vector<string>& words, string target) {
        Trie trie(words);
        mem.resize(target.size() + 1, -1);
        mem.back() = 0;
        this->target = target;
        this->root = trie.getRoot();
        int ans =  helper(root, 0);
        return ans >= 1e6 ? -1 : ans;
    }
};
/* 因為上面的修改會暴露struct node資料結構
 * 所以改進成以下的修改
 */
class Trie{
    struct node{
        array<node *, 26> m; // __important__ 因為vector不能馬上給定size所以使用array
    };
    struct node* root;
public:
    Trie() {
        root = new struct node();
    }
    Trie(vector<string>& words) : Trie() {
        for(auto& word : words)
            add(word);
    }
    void add(string& word) {
        struct node *p = root;
        for(char c : word) {
            c -= 'a';
            if(!p->m[c])
                p->m[c] = new struct node();
            p = p->m[c];
        }
    }
    vector<int> find(string& str, int idx) {
        struct node *p = root;
        vector<int> rtn;
        while(idx < str.size() && p && p->m[str[idx] - 'a']) {
            rtn.push_back(idx);
            p = p->m[str[idx] - 'a'];
            idx++;
        }
        return rtn;
    }
};
class Solution {
    int helper(Trie& trie, string& target, int idx) {
        if(~mem[idx]) return mem[idx];
        int ans = 1e6;
        for(auto&  p : trie.find(target, idx))
            ans = min(ans, 1 + helper(trie, target, p + 1));
        return mem[idx] = ans;
    }
    vector<int> mem;
public:
    int minValidStrings(vector<string>& words, string target) {
        Trie trie(words);
        mem.resize(target.size() + 1, -1);
        mem.back() = 0;
        int ans =  helper(trie, target, 0);
        return ans >= 1e6 ? -1 : ans;
    }
};
