/*  使用trie來儲存path
 *
 *  time  : O(NlogN + NM)
 *  space : O(NM)
 */
class Trie{
    struct node{
        unordered_map<string, node*> m;
        bool isEnd;
    };
    struct node* root;
public:
    Trie(){
        root = new struct node();
    }
    bool checkAndAdd(string& path) {
        istringstream iss(path);
        string str;
        struct node *p = root;
        bool isSubFolder{false};
        while(getline(iss, str, '/')) {
            if(!p->m.count(str))
                p->m[str] = new struct node();
            p = p->m[str];
            isSubFolder |= p->isEnd;
        }
        p->isEnd = true;
        return isSubFolder;
    }
};
class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        Trie trie;
        vector<string> ans;
        sort(begin(folder), end(folder)); // NlogN, N : size of folder
        for(auto& f : folder) {           // O(NM), M : maximum size of subfolder of one path
            if(!trie.checkAndAdd(f))
                ans.push_back(f);
        }
        return ans;
    }
};
/*
 *  參考解答
 *
 *  因為sort之後folder會根據字母排序 所以如果有subfolder一定會排在原本的之後
 *  例如 : "/a/b/c", "/a/b", "/a" 排序後 "/a", "/a/b", "/a/b/c"
 *  所以只要檢查ans.back() 是否是目前的substring即可
 *
 *  time  : O(NlogN + N) = O(NlogN)
 *  space : O(N + logN) = O(N)
 */
class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        vector<string> ans;
        sort(begin(folder), end(folder)); // __important__ 會照字母排序 只要檢查前一個string即可
        for(auto& f : folder) {
            if(ans.empty()) ans.push_back(f);
            else {
                int pos = f.find(ans.back() + "/");
                if(pos == string::npos || pos != 0) // __importatn__ 沒找到或是 找到了但是不是從0開始  例如 : "/c","/d/c/e"
                    ans.push_back(f);
            }
        }
        return ans;
    }
};
/*  2025/07/19 daily challenge
 *  第一次一樣寫了Trie的解法看了上面解答自己寫了下面的解答
 */
 class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        sort(begin(folder), end(folder));
        vector<string> rtn;
        for(auto& f : folder) {
            if(!rtn.empty()) {
                int pos = f.find(rtn.back() + "/"); //__important__ 要多找"/" 不然有可能找到 rtn.back() = "/a/b/c", f = "a/b/cd"
                if(pos == 0) continue;              //                        上面這種情況還是會找到
            }
            rtn.push_back(f);
        }
        return rtn;
    }
};
