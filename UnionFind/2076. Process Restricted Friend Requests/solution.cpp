/* ref : https://leetcode.com/problems/process-restricted-friend-requests/solutions/1576935/c-union-find-by-lzl124631x-re15/
 * 
 * 這題的重點是怎麼不連接的情況下，辨識所有的restriction都不會連接再一起  
 */
class UnionFind{
    vector<int> root, rank;
public:
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    UnionFind(int sz) : root(sz), rank(sz, 1) {
        iota(begin(root), end(root), 0);
    }
    int un(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return 0;
        if(rank[y] > rank[x]) swap(x, y);
        root[y] = x;
        return rank[x] += rank[y];
    }
    bool isConnect(int x, int y) {
        return find(x) == find(y);
    }
};

class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        UnionFind uf(n);
        vector<bool> rtn;
        for(auto& r : requests) {   // r[0], r[1]是預計要連接的node 分屬於group x和group y
            int gx = uf.find(r[0]); // 如果這兩個連接起來 那麼group x == group y
            int gy = uf.find(r[1]);
            bool check{true};
            if(!uf.isConnect(gx, gy)) {  
                for(auto& b : restrictions) {
                    int gp = uf.find(b[0]), gq = uf.find(b[1]);             // 檢查b[0]和b[1]所屬的group gp和gq
                    if((gx == gp && gy == gq) || (gx == gq && gy == gp)) {  // 是否因為group x == group y 之後會互通
                        check = false;                                      // 有四種情況
                        break;                                              // 1. gp == gx, gq == gx
                    }                                                       // 2. gp == gy, gq == g:y
                }                                                           // 3. gp == gx, gq == gy
            }                                                               // 4. gp == gy, gq == gx
            rtn.push_back(check);                                           // 目前程式檢查case 3和case 4
            if(check) uf.un(gx, gy);                                        // case 1和case 2不需要檢查?
        }                                                                   // 如果在同一個group gp == gq, 且qx==qy
        return rtn;                                                         // 上面的檢查就已經包含
    }
};
