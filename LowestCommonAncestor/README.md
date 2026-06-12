## Lowest Common Ancestor(LCA)

### 建立parent table
+ 參考 [1483. Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node/description/)
+ 從parent table找出最近的相同parent就是LCA
+ parent[i][j] 就是表示node i往上2^j個node之後是誰
+ 要從i往上走2^j, 要先知道2^(j - 1)
```cpp
int prev = parent[i][j - 1];         // 從i往上走 2^(j-1)
parent[i][j] = parent[prev][j - 1];  // 要抵達2^j, 從prev往上走2^(j-1)
```
+ 完整的code snippet
+ 每次遇到一個node就把parent[c][j] 順便也建立起來 因為建立的時候需要上面的node的parent table所以必須由上往下建立
+ parent[c][j] 是由parent[c][j - 1]建立的 所以第一個parent[c][0] 必須自己先填上去
```cpp
void dfs(int c, int p, int d) {
    depth[c] = d;
    parent[c][0] = p; // c往上一個是p
    for(int j = 1; j < log_max; ++j) {
        if(parent[c][j - 1] != -1) // 前2^(j - 1) 有parent的話
            parent[c][j] = parent[parent[c][j - 1]][j - 1];
        else break;
    }
    for(const auto& nxt : adj[c])
        if(nxt != p)
            dfs(nxt, c, d + 1);
}
```
### 查詢parent table
+ 我先往前跳最大的範圍2^j 如果parent一樣表示跳太多了 就少跳一點 j--
+ 直到找到 parent不一樣的點 那往上一個就是LCA
```cpp
int get_lca(int u, int v) {
    // 1. 先確保depth[u] >= depth[v]
    if(depth[u] < depth[v]) swap(u, v);

    // 2. 提升u的高度和v一樣
    int diff = depth[u] - depth[v];
    for(int j = 0; j < log_max; ++j)
        if((diff >> j) & 1)
            u = parent[u][j];
    if(u == v) return u;

    // 3. 兩個一起往上 從跳最大步的開始
    //    如果兩個parent一樣 表示跳太多了
    //            parent不一樣就往上跳
    for(int j = log_max - 1; j >= 0; --j) {
        if(parent[u][j] != parent[v][j]) {
            u = parent[u][j];
            v = parent[v][j];
        }
    }

    // 4. 再往上跳一個才是common ancestor
    return parent[u][0];
}
```
