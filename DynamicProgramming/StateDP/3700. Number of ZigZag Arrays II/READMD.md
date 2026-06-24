# 🚀 掌握矩陣快速冪：LeetCode 3700. Number of ZigZag Arrays II 完整題解

## 1. 怎麼思考這個題目？（解題核心訊號）

拿到題目時，先觀察測資範圍（Constraints），這是決定演算法走向的關鍵：
* $3 \le n \le 10^9$
* $1 \le l < r \le 75$

當你看到 **$n$ 竟然高達 $10^9$**，這是一個絕對的死刑宣告：所有時間複雜度為 $O(n)$ 的常規動態規劃（DP）或線性迴圈都會**逾時（TLE）**。我們必須在 $O(\log n)$ 的時間內解決它。

再看到數值範圍，最大值減最小值 $m = r - l + 1 \le 75$，**狀態的基數非常小**。
> 💡 **解題訊號**：**超大 $n$ 加上極小狀態數** $\rightarrow$ 這題是標準的 **「動態規劃 + 矩陣快速冪（Matrix Exponentiation）」** 大魔王題！

---

## 2. 狀態編碼（State Encoding）

要滿足「不出現連續三個嚴格遞增或遞減」的 ZigZag 條件，我們在放入下一個數字時，只需要知道**最後兩個元素的相對關係**。

我們把實際範圍 $[l, r]$ 平移映射到索引 $[0, m-1]$。一個合法的結尾狀態，可以用兩個核心資訊來代表：
1. `val` ($0 \le \text{val} < m$)：當前陣列最後一個元素的值。
2. `dir` ($0$ 或 $1$)：前一個元素到當前元素的趨勢。
   * `0`（下降）：代表（前數 $>$ 當前數）。因為這次是下降，下一個數**必須上升**。
   * `1`（上升）：代表（前數 $<$ 當前數）。因為這次是上升，下一個數**必須下降**。

為了方便用矩陣運算，我們將這兩個維度壓縮成一個一維的狀態編號（總共有 $2m$ 個狀態）：
$$\text{id}(\text{val}, \text{dir}) = \text{dir} \times m + \text{val}$$

---

## 3. 怎麼找到狀態轉移矩陣？

轉移矩陣 $T$ 的大小為 $2m \times 2m$，它的定義是：**`T[下一個狀態][當前狀態]`**。如果可以合法轉移，值就為 `1`，否則為 `0`。

我們可以把這個大矩陣切成 4 個大小為 $m \times m$ 的子區塊：



* **區塊 A & D（連續兩次下降或上升）**：因為不符合 ZigZag 規則，全部填 `0`。
* **區塊 B（下降 $\rightarrow$ 上升）**：當前最後一個數是 $y$（下降狀態 `id(y, 0)`），下一個數 $x$ 必須大於 $y$（$y < x$），轉移到上升狀態 `id(x, 1)`。這會形成一個**下三角矩陣**。
* **區塊 C（上升 $\rightarrow$ 下降）**：當前最後一個數是 $y$（上升狀態 `id(y, 1)`），下一個數 $x$ 必須小於 $y$（$y > x$），轉移到下降狀態 `id(x, 0)`。這會形成一個**上三角矩陣**。

---

### 💡 實戰拆解：以 $m = 3$ 為例，從轉移算式到矩陣的推導

為了不再被抽象的代數符號轟炸，我們直接用 $m = 3$（假設數值範圍平移後只有 $0, 1, 2$）來實際列出所有的轉換算式。

#### ① 狀態編號對照表
根據編碼公式 `id(val, dir) = dir * 3 + val`：
* **下降狀態 (`dir = 0`)**：狀態 `0` ($val=0$)、狀態 `1` ($val=1$)、狀態 `2` ($val=2$)
* **上升狀態 (`dir = 1`)**：狀態 `3` ($val=0$)、狀態 `4` ($val=1$)、狀態 `5` ($val=2$)

#### ② 列出所有的狀態轉移算式 (Transition Equations)
根據 ZigZag 的規則，我們來思考「**下一階段的新狀態，可以由哪些舊狀態轉移而來？**」

* **如何到達「新下降狀態」？**（下一步必須比上一步小，所以前一步必須是**上升狀態**，且數值比現在大）
  * 新狀態 0 ($val=0$)：前一步可以是狀態 4 ($val=1$) 或狀態 5 ($val=2$) $\rightarrow$ $\text{新 } DP[0] = DP[4] + DP[5]$
  * 新狀態 1 ($val=1$)：前一步只能是狀態 5 ($val=2$) $\rightarrow$ $\text{新 } DP[1] = DP[5]$
  * 新狀態 2 ($val=2$)：沒有比 2 更大的上升狀態 $\rightarrow$ $\text{新 } DP[2] = 0$

* **如何到達「新上升狀態」？**（下一步必須比上一步大，所以前一步必須是**下降狀態**，且數值比現在小）
  * 新狀態 3 ($val=0$)：沒有比 0 更小的下降狀態 $\rightarrow$ $\text{新 } DP[3] = 0$
  * 新狀態 4 ($val=1$)：前一步只能是狀態 0 ($val=0$) $\rightarrow$ $\text{新 } DP[4] = DP[0]$
  * 新狀態 5 ($val=2$)：前一步可以是狀態 0 ($val=0$) 或狀態 1 ($val=1$) $\rightarrow$ $\text{新 } DP[5] = DP[0] + DP[1]$

#### ③ 轉換為矩陣形式 (Matrix Form)
現在，我們把上面這 6 個轉移算式，改寫成線性代數的「矩陣 $\times$ 向量」形式：

```math
\begin{bmatrix}
\text{新 } DP[0 = id(0, down)] \\
\text{新 } DP[1 = id(1, down)] \\
\text{新 } DP[2 = id(2, down)] \\
\text{新 } DP[3 = id(0, up)] \\
\text{新 } DP[4 = id(1, up)] \\
\text{新 } DP[5 = id(2, up)]
\end{bmatrix}
=
\begin{bmatrix}
0 & 0 & 0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0 & 0 & 1 \\
0 & 0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 & 0 \\
1 & 0 & 0 & 0 & 0 & 0 \\
1 & 1 & 0 & 0 & 0 & 0
\end{bmatrix}
\times
\begin{bmatrix}
DP[0 = id(0, down)] \\
DP[1 = id(1, down)] \\
DP[2 = id(2, down)] \\
DP[3 = id(0, up)] \\
DP[4 = id(1, up)] \\
DP[5 = id(2, up)]
\end{bmatrix}
```

中間那個充滿 `0` 與 `1` 的 $6 \times 6$ 方陣，就是我們要找的**狀態轉移矩陣 $T$**！

#### ④ 觀察轉移矩陣 $T$ 的規律
把這個矩陣放大來看，你會發現它其實由四個 $3 \times 3$ 的區塊組成：

```text
               舊狀態 (From)
           【下降】     【上升】
            0  1  2      3  4  5
          ┌───────────┬───────────┐
     0    │ 0  0  0   │  0  1  1  │ ──> 區塊 B (右上)：上三角矩陣 (y > x)
下一 1    │ 0  0  0   │  0  0  1  │
狀態 2    │ 0  0  0   │  0  0  0  │
(To)      ├───────────┼───────────┤
     3    │ 0  0  0   │  0  0  0  │
     4    │ 1  0  0   │  0  0  0  │ ──> 區塊 C (左下)：下三角矩陣 (y < x)
     5    │ 1  1  0   │  0  0  0  │
          └───────────┴───────────┘
```
這完美對應了程式碼中，我們用雙層迴圈填寫矩陣的邏輯：
+ 當 $y < x$ 時，將 T[id(x, 1)][id(y, 0)] 填入 1（左下角的下三角）。
+ 當 $y > x$ 時，將 T[id(x, 0)][id(y, 1)] 填入 1（右上角的上三角）。

## 4. 推導最終結果

矩陣與狀態向量（Vector）相乘，本質上就是在做「所有狀態的一步同步更新」。
假設長度為 $2$ 的初始合法組合數向量為 $V_2$。

* 長度為 $3$ 的狀態：$V_3 = T \times V_2$
* 長度為 $n$ 的狀態：$V_n = T^{n-2} \times V_2$

利用**矩陣快速冪**，我們可以在 $O(m^3 \log n)$ 的時間內算出 $P = T^{n-2}$，最後把 $P \times V_2$ 向量裡的所有元素加總，就是答案！

---

## 5. 易讀、易懂的 C++ 程式碼

這份程式碼將矩陣運算獨立封裝，並加上詳細註解，結構非常清晰：

```cpp
#include <vector>

using namespace std;

class Solution {
private:
    const int MOD = 1e9 + 7;
    using Matrix = vector<vector<long long>>;

    // 1. 標準矩陣乘法工具 (C = A * B)
    Matrix multiply(const Matrix& A, const Matrix& B) {
        int sz = A.size();
        Matrix C(sz, vector<long long>(sz, 0));
        for (int i = 0; i < sz; i++) {
            for (int k = 0; k < sz; k++) {
                if (A[i][k] == 0) continue; // 剪枝優化
                for (int j = 0; j < sz; j++) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    // 2. 矩陣快速冪 (計算 base^exp)
    Matrix power(Matrix base, long long exp) {
        int sz = base.size();
        Matrix result(sz, vector<long long>(sz, 0));
        for (int i = 0; i < sz; i++) result[i][i] = 1; // 初始化為單位矩陣

        while (exp > 0) {
            if (exp & 1) result = multiply(result, base);
            base = multiply(base, base);
            exp >>= 1;
        }
        return result;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        int states = 2 * m;

        // 狀態編碼 Lambda 函式
        auto id = [&](int val, int dir) {
            return dir * m + val;
        };

        // 3. 建立轉移矩陣 T
        Matrix T(states, vector<long long>(states, 0));
        for (int x = 0; x < m; x++) {
            // 下降 -> 上升 (下一步的數 x 必須大於當前的數 y)
            for (int y = 0; y < x; y++) {
                T[id(x, 1)][id(y, 0)] = 1;
            }
            // 上升 -> 下降 (下一步的數 x 必須小於當前的數 y)
            for (int y = x + 1; y < m; y++) {
                T[id(x, 0)][id(y, 1)] = 1;
            }
        }

        // 4. 初始化長度為 2 的狀態向量 (start vector)
        vector<long long> start(states, 0);
        for (int a = 0; a < m; a++) {
            for (int b = 0; b < m; b++) {
                if (a == b) continue; // 不能相等
                if (a < b)  start[id(b, 1)]++; // 遞增趨勢 (上升)
                else        start[id(b, 0)]++; // 遞減趨勢 (下降)
            }
        }

        // 5. 計算 T^(n-2)
        Matrix P = power(T, n - 2);

        // 6. 將轉移後的矩陣 P 與初始向量 start 相乘，並統計總方法數
        long long total_arrays = 0;
        for (int i = 0; i < states; i++) {
            long long current_state_sum = 0;
            for (int j = 0; j < states; j++) {
                current_state_sum = (current_state_sum + P[i][j] * start[j]) % MOD;
            }
            total_arrays = (total_arrays + current_state_sum) % MOD;
        }

        return total_arrays;
    }
};
```
