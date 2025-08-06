## Reference
+ [Segment Tree](https://www.geeksforgeeks.org/segment-tree-data-structure/)
## Introduction
![](https://hackmd.io/_uploads/S12Ds0gin.png)
+ Segment Tree是一種data structure，可以有效的update, query某個區域的elements。通常是$O(logN)$。
### 特性
+ Segment Tree為binary tree，leaf node為array element。
+ 內部node，為某個區間的特性。例如:某個區間的和，或是某個區間的最大值/最小值。
+ root node為整個區間的特性。例如:全部的和，或是全部的最大值/最小值。
### 種類
+ **Sum segment tree**: 它存儲array每個區間中的元素和，用於需要對element之和進行有效query和update的問題。
+ **Min/Max segment tree**:它存儲array每個區間中的最大最小值。
+ **Range update segment tree/Lazy tree** : 可以有效的update某個區間的elements。
### Segment tree中操作種類
+ Addition/Subtraction
+ Maximum/Minimum
+ GCD/LCM
+ AND/OR/XOR
### 建立Segment tree
在建立segment tree之前，先思考以下問題。
1. 根據問題來決定leaf node要儲存什麼?
2. parent node要怎麼從child node得到?
## Code snippet
### 建立segment tree
```cpp=
vector<int> ST; // segment tree
vector<int> nums;

// node: 在Segment tree中的index
// left, right: 為此node在vector中代表的區間
// 例如 ST[1] 代表的是全部的區間，[0, sz - 1]
//     ST[2] 為ST[1]的左子樹代表[0, (sz - 1) / 2]
//     ST[3] 為ST[1]的右子樹代表[(sz - 1) / 2 + 1, sz - 1]
void build(int node, int left, int right) {
    if(left == right)
        ST[node] = nums[left];
    else{
        int mid = (left + right) / 2;
        build(2 * node, left, mid);
        build(2 * node + 1, mid + 1, right);
        // 因為我們是建立Sum segment tree
        // 所以parent node = left node + right node
        ST[node] = ST[2 * node] + ST[2 * node + 1];
    }
}
// 如果N為2的倍數，則Segment tree為2*N - 1。
// 如果N非2的倍數，則取下一個2的倍數，例如2^j + 1--> 2^(j + 1)
// N = 2^j + 1
// 2^(j + 1) = 2^j * 2 = (N - 1) * 2 = 2N - 2
// segment tree取兩倍長度 2(2N - 2) = 4N
ST.resize(4 * nums.size());
// 在segment tree中index = 1為蜷曲段的特性值
// 因為使用vector來表示binary tree，root要從1開始。
build(1, 0, n - 1); 
```
### 更新segment tree
// node        : 為segment tree中的index
// left, right : node代表在vector中的區間
// idx, val    : 為原本vector中的index和新的數值。
```cpp=
void update(int node, int left, int right, int idx, int val) {
    // out of range
    if(idx < left or idx > right) return;
    else if(left == right) { // 更新leaf node
        ST[node] = val;
        nums[idx] = val;
    } else {
        int mid = (left + right) / 2;
        update(2 * node, left, mid, idx, val);
        update(2 * node + 1, mid + 1, right, idx, val);
        // 因為更新過leaf node也要更新parent node
        ST[node] = ST[2 * node] + ST[2 * node + 1];
    }
}
update(0, 0, sz - 1, idx, val);
```
### 查詢segment tree
```cpp=
// node, : 為segment tree中的index
// tl, tr, l, r: 為vector中的區間, 其中 tl, tr為node代表在vector中區間，ql, qr為欲查詢的區間。
int query(int node, int tl, int tr, int ql, int qr) {
    // 欲查詢的區間在node代表的區間[tl, tr]之外
    if(qr < tr or ql > tr) 
        return 0;
    // 欲查詢的區間包含node代表的區間[tl, tr]
    if(ql <= tl and qr >= tr)
        return ST[node];
    // 因為我們要往child繼續查詢，
    // 必須更新node代表的區段
    int tm = (tr + tl) / 2;
    return update(2 * node, tl, tm, ql, qr) +
           update(2 * node + 1, tm + 1, tr, ql, qr);
}
```
### Time/Space complexity
+ time complexity

| build | update | query |
| -------- | -------- | -------- |
| $O(4N) = O(N)$| $O(logN)$| $O(logN)$     |

+ space complexity
因為建立segment tree使用了4N的vector，所以$O(4N) = O(N)$
## Lazy propagation
+ ==update一個區段，可以使用lazy propagation。==
+ 如果需要update從element i到element j，每個element都執行 nums[i] += val，則可以使用lazy propagation。
+ 照理說range內的element每個數值改變，要執行多次update。
+ 因為是Sum segment tree，所以可以對增減的數值先keep住。
+ 使用vector<int> lazy來表示這個node需不需要update。

### Code snippet
#### build 建立segment tree
+ 這個function和一般的Segment tree一樣。
```cpp=
vector<int> nums; // input vector
vector<int> ST, lazy;
// lazy[i] == 0 : 表示不需要更新
// lazy[i] != 0 : 需要更新
int sz;
void build(int n, int l, int r)
{
    if(l == r) ST[n] = nums[l];
    else {
        int mid = (l + r) / 2;
        build(2 * n, l, mid);
        build(2 * n + 1, mid + 1, r);
        ST[n] = ST[2 * n] + ST[2 * n + 1];
    }
}
sz = nums.size();
ST.resize(4 * sz);
lazy.resize(4 * sz);
build(1, 0, sz - 1);
```
### query 查詢某個range之和
```cpp=
int query(int n, int tl, int tr, int ql, int qr)
{
    // 先確認此node需不需要把update value往下推
    if(lazy[n] != 0) {
        // 因為這個parent node有(tr - tl + 1)個element
        ST[n] += (tr - tl + 1) * lazy[n];
        // 如果不是leaf node，把update往下推
        if(tr != tl) {
            lazy[2 * n] += lazy[n];
            lazy[2 * n + 1] += lazy[n];
        }
        // 表示ST[n] 已經update過了。
        lazy[n] = 0; 
    }
    // ------ 以下和正常的Segment tree流程一樣 ------ //
    // out of range
    if(qr < tl or tr < ql) 
        return 0;
    // 查詢range包含目前的range
    if(ql <= tl and qr >= tr)
        return ST[n];
    
    int tm = (tl + tr) / 2;
    return query(2 * n, tl, tm, ql, qr) + 
           query(2 * n + 1, tm + 1, tr, ql, qr);
}
```
### update 某個區間所有值
```cpp=
void update(int n, int tl, int tr, int ul, int ur, int diff)
{
    // 先檢查lazy[n]，表示有之前的update
    if(lazy[n] != 0) {
        ST[n] += (tr - tl + 1) * lazy[n];
        if(tl != tr) {
            lazy[2 * n] += lazy[n];
            lazy[2 * n + 1] += lazy[n];
        }
        lazy[n] = 0;
    }
    // out of range
    if(ur < tl or tr < ul) return;
    
    // 這次的update操作
    // update區域包含此node的區域
    if(ul <= tl and ur >= tr) {
        // update目前的node
        ST[n] += (tr - tl + 1) * diff; 
        // 只把update值往下推，不進行update
        if(tl != tr) {
            lazy[2 * n] += diff;
            lazy[2 * n + 1] += diff;
        }
        // **返回，不繼續往下update。**
        return;
    }
    int tm = (tl + tr) / 2;
    update(2 * n, tl, tm, ul, ur, diff);
    update(2 * n + 1, tm + 1, tr, ul, ur, diff);
    // 因為更新過child，所以必須更新ST[n]
    // 執行update，更新range包含node range就會跟新child
    ST[n] = ST[2 * n] + ST[2 * n + 1];
}
```
## Dynamic Segment Tree
+ 前面的例子都是從vector來建立segment tree，有的情況是不知道目前的內容，需要一步一步建立，就必須動態建立segment tree。
+ 和建立binary tree一樣，每個child代表不同區間。
+ 和正常的segment tree一樣，每個node都會有表示的區間。
### Code snippet
#### build 建立dynamic segment tree     
+ 因為是dynamic建立，所以在update的同時會建立，不需要這份code。
+ 但是需要定義node，和建立root node。
+ 這邊使用shared_ptr來避免memory leakage。
    
```cpp=
template<typename T>
class DynamicSegmentTree {
    struct node{
        T val;
        shared_ptr<node> left, right;
        node(T _val) : val(_val), left(nullptr), right(nullptr) {}
    };
    int sz;
    shared_ptr<node> root;
public:
    DynamicSegmentTree(int _sz) : sz(_sz)
    {
        // 建立root node
        root = make_shared<node>(0);
    }
};
```
### update 某個index的value
+ 如果沒有node就建立node
+ 直到找到leaf node且 left == index
```cpp=
template<typename T>
class DynamicSegmentTree {
    void _update(shared_ptr<node> p, int left, int right, int idx, T val)
    {
        // out of range
        if(idx < left or right < idx) return;

        // leaf node 且 left == right == idx
        if(left == right && left == idx) {
            p->val = val;
            return;
        }

        // 遞迴的尋找index的leaf node
        int mid = left + (right - left) / 2;
        if(idx <= mid) { // in left child
            if(!p->left)
                p->left = make_shared<node>(0);
            _update(p->left, left, mid, idx, val);
        } else { // in right child
            if(!p->right)
                p->right = make_shared<node>(0);
            _update(p->right, mid + 1, right, idx, val);
        }

        // 因為child數值更新了，所以更新parent
        T sum1{}, sum2{};
        if(p->left) sum1 = p->left->val;
        if(p->right) sum2 = p->right->val;

        p->val = sum1 + sum2;
        return;
    }
public:
    void update(int idx, T val) {
        // root表示[0, sz - 1]的區間
        _update(root, 0, sz - 1, idx, val);
    }
};
```
### query 查詢某個range之和
```cpp=
template<typename T>
class DynamicSegmentTree {
    T _query(shared_ptr<node> p, int tl, int tr, int ql, int qr)
    {
        // node不存在
        if(p == nullptr) return 0;

        // out of range
        if(qr < tl or tr < ql)
            return 0;

        // including this range
        if(ql <= tl and qr >= tr)
            return p->val;

        int tm = tl + (tr - tl) / 2;
        return _query(p->left, tl, tm, ql, qr) +
               _query(p->right, tm + 1, tr, ql, qr);
    }
public:
    T query(int left, int right) 
    {
        return _query(root, 0, sz - 1, left, right); 
    }
};
```
