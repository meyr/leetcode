class Trie{
    struct node{
        unordered_map<char, shared_ptr<node>> m;
    };
    shared_ptr<node> root;
    void add(string& str) {
        shared_ptr<node> p = root;
        for(auto& c : str) {
            if(!p->m[c])
                p->m[c] = make_shared<node>();
            p = p->m[c];
        }
    }
public:
    Trie(vector<int>& nums) {
        root = make_shared<node>();
        for(auto& n : nums) {
            string str = to_string(n);
            add(str);
        }
    }
    int find(int n) {
        shared_ptr<node> p = root;
        string str = to_string(n);
        int i = 0;
        for(; i < str.size(); ++i) {
            if(p->m.count(str[i]))
                p = p->m[str[i]];
            else break;
        }
        return i;
    }
};
class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        Trie trie(arr1);
        int ans{};
        for(auto& n : arr2)
            ans = max(ans, trie.find(n));
        return ans;
    }
};
