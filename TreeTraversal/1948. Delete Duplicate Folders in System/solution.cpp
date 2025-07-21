/*  ref : https://leetcode.com/problems/delete-duplicate-folders-in-system/solutions/6980131/100-folder-deduplication-with-just-two-d-stzj/
 *  
 *  這題看了很久 主要是題目看不太懂
 *  一個folder如果被判斷成相, 並非名字相同 而是需要子資料夾名字和結構都相同
 *  例如: a-->b-->c   資料夾a底下有b, b底下有c, c是個空資料夾
 *        z-->b-->c   資料夾z底下有b, b底下有c, c是個空資料夾     我們可以視為 a和 z是相同
 *
 *  因為題目要求把相同的刪掉 所以a和z可以被刪除
 *
 *  為了判斷資料夾是否相同 我們必須建立signature就是針對subfolder的結構產生一個string
 *  例如:         a------------->b------->c
 *  signature     (b(c()))     (c())     ()
 *               底下有個b    底下有一個c                  () 代表empty
 *
 *  統計每個signature就是針對每個sufolder的特性來統計
 *  如果count of signature > 1 表示有重複的subfolder 我們就可以刪除掉
 *
 */
class Solution {
    struct node{        // 使用struct node來記錄每個folder的特性
        string name;
        unordered_map<string, node *> child;
        string signature;
        node(const string& _name) : name(_name){}
    };
    struct node* root;
    unordered_map<string, int> signatureCnt;
    string helper1(struct node* root) {
        if(root->child.empty()) return "()";
        vector<string> sigs;                    // 先收集所有child的signature
        for(auto& [n, ch] : root->child) {
            sigs.push_back(n + helper1(ch));
        }
        sort(begin(sigs), end(sigs));           // __importatn__ 排序後再把signature接起來 避免有順序不一樣的相同signature
        string rtn{"("};
        for(auto& sig : sigs)
            rtn += sig;
        rtn += ")";
        root->signature = rtn;
        signatureCnt[root->signature]++;
        return rtn;
    }
    void helper2(struct node* root, vector<string>& cur, vector<vector<string>>& rtn) {
        if(!root->child.empty() and signatureCnt[root->signature] > 1) return;
        cur.push_back(root->name);
        rtn.push_back(cur);
        for(auto& [name, child] : root->child)
            helper2(child, cur, rtn);
        cur.pop_back();
    }
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        root = new node("");
        for(auto& path : paths) {   // each path
            struct node* p = root;
            for(auto& f : path) {   // each subfolder
                if(!p->child.count(f))                  // 當此folder不存在就建立
                    p->child[f] = new node(f);
                p = p->child[f];
            }
        }
        // create signature from bottom to top
        helper1(root);

        // remove duplicate
        vector<vector<string>> rtn;
        vector<string> cur;
        for(auto& [name, child] : root->child)
            helper2(child, cur, rtn);

        return rtn;
    }
};
