## Sparse Table
+ 目的是為了解決 RMQ 問題 (Range Minimum/Maximum Query，區間極值查詢)。
+ 預處理（只需要 $O(N \log N)$ 的時間和空間
+ 查詢速度 $O(1)$

### 2的次方長度
+ 為什麼叫「稀疏」表？因為它不記錄所有長度的答案，它只記錄長度為 1, 2, 4, 8, 16, 32...（也就是 $2^j$） 的區間答案。
	+ st[i][0]：從索引 i 開始，長度為 $2^0 = 1$ 的區間極值（其實就是數字自己）
	+ st[i][1]：從索引 i 開始，長度為 $2^1 = 2$ 的區間極值
	+ st[i][2]：從索引 i 開始，長度為 $2^2 = 4$ 的區間極值
	+ st[i][3]：從索引 i 開始，長度為 $2^3 = 8$ 的區間極值

### 建表
我們要算長度為 4 的區間，可以怎麼算？
答案是：拿兩個長度為 2 的區間拼起來！

例如，我想知道從索引 0 開始、長度為 4 的區間 [3, 2, 4, 5] 的最大值：
	+ 前半段：從索引 0 開始、長度為 2 的區間 [3, 2] $\rightarrow$ 最大值是 3。
	+ 後半段：從索引 2 開始、長度為 2 的區間 [4, 5] $\rightarrow$ 最大值是 5。
	+ 我只要比較 max(3, 5)，就知道這 4 個數字的最大值是 5。

1. 當長度為1 也就是只有一個element, j = 0, 2^j = 1, st[i][0] = nums[i] 就是等於自己
2. 當長度為2, 4, 8, ... 因為是2的倍數 我們一定可以分成兩半 前半段是st[i][j - 1], 後半段是 st[i + (1 << (j - 1))][j - 1]
```cpp
        for (int i = 0; i < n; i++) {
            st[i][0] = nums[i];
        }
        for (int j = 1; j < logn; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] =
                    max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
```

### 查詢任意區間
因為我們要找的是「最大值」或「最小值」，這類問題有一個特性：__區間重複計算__了也沒關係。
利用這個特性，當有人問你一個奇形怪狀的長度（例如問你索引 1 到 6，長度是 6），我們不需要大費周章去湊 4 + 2。
我們只需要找一個小於等於 6、且最大的「2的次方」，那就是 4 ($2^2$)。
接著，我們用兩個長度為 4 的區間，把你想問的範圍頭尾蓋住：
	第一塊（左邊對齊頭）：從索引 1 開始，長度為 4 的區間（涵蓋索引 1, 2, 3, 4）。
	第二塊（右邊對齊尾）：結尾在索引 6，長度為 4 的區間（涵蓋索引 3, 4, 5, 6）。

1. 欲查詢的區間是[left, right]
2. 先計算區間長度 sz = right - left + 1
3. 計算小於等於sz最大的2的冪次 j = 31 - __builtin_clz(sz)
4. 因為重複覆蓋相同的區域是沒關係的, 取用max(st[left][j], st[right - (1 << j) + 1][j]
```cpp
   0  1        7   8
   |----------|        st[0][3]
      |------------|   st[1][3]   使用這兩個區域就可以完整覆蓋[0, 8]
```
```cpp
int query(int left, int right) {
	int j = 31 - __builtin_clz(right - left + 1);
    return max(stMax[left][j], stMax[right - (1 << j) + 1][j]);
}
```
### code snippet
+ 加上可以輸入任意的比較function和可以輸入任意的data type成為以下的code snippet
```cpp
template<typename T>
class SparseTable {
private:
    using compartor = function<T(T&, T&)>;
    vector<vector<T>> st;
    compartor op;
public:
    SparseTable(const vector<int>& nums, const compartor& func) {
        auto n = nums.size();
        if (n == 0) return;
        op = move(func);
        auto logn = sizeof(T) * 8 - __builtin_clz(n);
        st.resize(n, vector<T>(logn));

        for (auto i = 0; i < n; i++)
            st[i][0] = nums[i];

        for (auto j = 1; j < logn; j++) {
            for (auto i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = op(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r) {
        auto j = (sizeof(T) * 8 - 1) - __builtin_clz(r - l + 1);
        return op(st[l][j], st[r - (1 << j) + 1][j]);
    }
};
```
### 除了maximun/minimum之外
1. 最大公因數 (GCD) / 最小公倍數 (LCM)
2. 位元運算的 AND (&) 與 OR (|)

### problems
239. Sliding Window Maximum
1521. Find a Value of a Mysterious Function Closest to Target
2444. Count Subarrays With Fixed Bounds
