/*
 *      參考官方解答 : https://leetcode.com/problems/palindromic-path-queries-in-a-tree/solutions/8574521/palindromic-path-queries-in-a-tree-by-le-l02r/
 *
 *      1. 一個樹內的unique path組成的string是否可以拼成palindrome? 就是統計每個字母的特數 單數個數 <= 1就可以
 *                                                                  這邊可以使用bitmask和XOR
 *
 *      2. 題目雖然說是undirected tree但是使用directed tree會比較好理解 所以取node 0 當成是root
 *      3. node u --> node v 的path會變成 pref[u] = root->...->w--->u
 *                                        pref[v] = root->...->w--->v       其中pref[u]為root到node u經過的char的xor, w為共同的LCA
 *
 *         所以node u--> node v = prev[u] ^ prev[v] =  u-->v without w, 因為 w是共同的祖先 xor之後會不見 必須把它加回來
 *                              = prev[u] ^ prev[v] ^ mask[w]           其中mask[w] = 1 << (char(w) - 'a')
 *
 *      4. 修改某一個node等於是 此node的subtree都會修改到 __importatn__
 *         因為我們有了root, 所以每個路徑只會在subtree內連接
 *
 *         __Eular tour__ 把tree變成一維陣列 只需要幾綠每個node的進入時間tin[u]和 出node時間tout[u],
 *                                           根據tin[u]和tout[u]就可以知道subtree有哪些node
 *
 *                  void dfs(int u, int p) {
 *                      // 1. 記錄進入的時間點，並把節點放入一維陣列中
 *                      tin[u] = ++timer;
 *                      flat_array.push_back(u);
 *
 *                      // 2. 遞迴走訪所有子節點
 *                      for (int v : adj[u]) {
 *                          if (v != p) {
 *                              dfs(v, u);
 *                          }
 *                      }
 *
 *                      // 3. 記錄離開的時間點（此時子樹全部走訪完畢）
 *                      tout[u] = timer;
 *                  }
 *
 *       5. 既然是一維陣列就可以使用 差分陣列 + 樹狀陣列（BIT）來記錄和查詢 區域xor的總和
 */

class BIT {
private:
    vector<int> tree;
    int n;

public:
    BIT(int _n) : n(_n), tree(_n + 1) {}

    static int lowbit(int x) { return x & -x; }

    void update(int x, int v) {
        while (x <= n) {
            tree[x] ^= v;
            x += lowbit(x);
        }
    }

    int query(int x) {
        int ret = 0;
        while (x) {
            ret ^= tree[x];
            x -= lowbit(x);
        }
        return ret;
    }

    void updateRange(int l, int r, int v) {
        update(l, v);
        update(r + 1, v);                               // 因為是差分陣列 所以在r+1才恢復
    }
};

class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s,
                                vector<string>& queries) {
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        int LOG = 32 - __builtin_clz(n);
        vector<vector<int>> fa(n, vector<int>(LOG));
        vector<int> dep(n), l(n), r(n);
        int timer = 0;

        auto dfs = [&](auto&& dfs, int u, int p) -> void {
            l[u] = ++timer;                                     // 紀錄進入node時間
            fa[u][0] = p;                                       // 紀錄跳 2^0 = 1個往上的node是p
            for (int v : g[u]) {
                if (v == p) {
                    continue;
                }
                dep[v] = dep[u] + 1;                            // 紀錄depth
                dfs(dfs, v, u);
            }
            r[u] = timer;                                       // 紀錄離開node時間
        };
        dfs(dfs, 0, 0);

        for (int j = 1; j < LOG; ++j) {                         // __important__ 完整fa陣列  剛剛只記錄 2^0 = 1, 所以i = 1 開始
            for (int i = 0; i < n; ++i) {
                fa[i][j] = fa[fa[i][j - 1]][j - 1];             // 跳 2^i = 先跳2^(i-1) 再往前跳 2^(i-1)
            }
        }

        auto lca = [&](int u, int v) {                          // __important_ 表準的尋找LCA方法
            if (dep[u] < dep[v]) {                              // 保證 dep[u] >= dep[v]
                swap(u, v);
            }
            int diff = dep[u] - dep[v];                         // 兩個node的深度差異
            for (int i = 0; i < LOG; ++i) {                     // 因為dep[u] 比較深 所以開始上升diff
                if ((diff >> i) & 1) {
                    u = fa[u][i];
                }
            }
            if (u == v) {                                       // 上升到同一個高度之後兩個一樣 u就是LCA
                return u;
            }
            for (int i = LOG - 1; i >= 0; --i) {                // 先測試跳最大高度 確定是否一樣 如果不一樣表示需要跳 那就把u, v先跳到這個位置
                if (fa[u][i] != fa[v][i]) {                     //                               如果一樣表示跳過頭了 那就減少i繼續跳
                    u = fa[u][i];
                    v = fa[v][i];
                }
            }
            return fa[u][0];
        };

        BIT bit(n + 1);
        for (int i = 0; i < n; ++i) {                                   // 設定BIT的每個node數值
            bit.updateRange(l[i], r[i], 1 << (s[i] - 'a'));
        }

        vector<bool> ans;
        for (string& q : queries) {
            stringstream ss(q);
            string op;
            ss >> op;
            if (op == "update") {
                int u;
                char c;
                ss >> u >> c;
                bit.updateRange(l[u], r[u],
                                (1 << (s[u] - 'a')) ^ (1 << (c - 'a')));
                s[u] = c;
            } else {
                int u, v;
                ss >> u >> v;
                int w = lca(u, v);
                int mask =
                    bit.query(l[u]) ^ bit.query(l[v]) ^ (1 << (s[w] - 'a'));
                ans.push_back(__builtin_popcount(mask) <= 1);
            }
        }
        return ans;
    }
};
