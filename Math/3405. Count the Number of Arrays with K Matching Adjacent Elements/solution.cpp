/*  參考 : https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/solutions/6199516/python-easy-and-short-by-lee215-nl2i/
 *  還有gemini的解說
 *
 *  A, B, C, D, E      n = 5, k = 2, m = 2  長度為5的array 選出2個index相鄰一樣
 *
 *  1. 先選出k=2的index, 可以從B,C,D,E中選出兩個表示和前面一樣 所以是comb(n - 1, k) =   (n-1)!
 *                                                                                    ----------
 *                                                                                     k!(n-1-k)!
 *
 *  2. 選到之後剩下的空格可以任意填入數值
 *     例如選到 C,D 則  A, B, B, B, E           
 *                         --------
 *     或是選到 B,C 則  A, A, A, D, E
 *                      -------
 *     或是選到 B,E 則  A, A, C, D, D               ---> 這些組合最後都變成   X, Y, Z  (n-k = 5-2 = 3)三個block, 每個block都需要不同數字
 *                      ----     ----
 *
 *  3. 計算合併後的block排列數
 *     第一個block有m種選擇 其他因為要跟後面不一樣 所以只剩m-1種選擇 所以是 m * pow(m-1, n-k-1)
 *                  
 *     X,  Y,   Z
 *     m* m-1* m-1
 *
 *  4. 最後解答是 m * pow(m-1, n-k-1) * comb(n-1, k)   
 */
// 定義模數
long long MOD = 1e9 + 7;

// 快速冪函式：計算 (base^exp) % MOD
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) { // 如果 exp 是奇數
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD; // base 變成 base^2
        exp /= 2; // exp 除以 2
    }
    return res;
}

// 計算組合數 C(n, k) = n! / (k! * (n-k)!)
// 需要計算階乘和模逆元
long long nCr_mod_p(int n, int r) {
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (r > n / 2) { // 利用 C(n, k) = C(n, n-k)
        r = n - r;
    }

    // 計算階乘
    std::vector<long long> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    // 計算 C(n, r) = (n! * (r!)^(-1) * ((n-r)!)^(-1)) % MOD
    // 其中 (X)^(-1) 是 X 在 MOD 下的模逆元
    // 模逆元可以用快速冪的 power(X, MOD - 2) 來計算 (費馬小定理)
    long long numerator = fact[n];
    long long denominator = (fact[r] * fact[n - r]) % MOD;

    return (numerator * power(denominator, MOD - 2)) % MOD;     //__important__ 因為計算    n!             需要除數, 所以計算modular inverse後可以用乘法
                                                                //                       -------- % mod
                                                                //                       k!(n-k)!
}                                                               //
                                                                //               A*B mod M = 1, 稱B為A的modular inverse
                                                                //               pow(A, M-1) mod M = 1 (費馬小定理證實了) 所以
                                                                //               A*pow(A, M-2) mod M = 1  --> pow(A, M-2) 為A的modular inverse
class Solution {
public:
    int countGoodArrays(int n, int m, int k) {
        // 檢查邊界條件，例如當 k 導致 n-k-1 為負數時
        // 原始Python code是 `pow(m - 1, n - k - 1, mod)`
        // 若 n - k - 1 < 0，則次方數為負，這在通常的組合問題中不常見，可能需要進一步確認題意
        // 如果 n - k - 1 < 0，例如當 k >= n - 1 時
        // 這裡預設問題的條件會保證 n - k - 1 >= 0
        if (n - k - 1 < 0) {
            // 根據具體問題的定義來處理，可能是回傳 0 或其他值
            // 在此範例中，我們假設輸入會讓 n-k-1 >= 0
            return 0;
        }

        long long term1 = m;
        long long term2 = power(m - 1, n - k - 1);
        long long term3 = nCr_mod_p(n - 1, k);

        long long result = (term1 * term2) % MOD;
        result = (result * term3) % MOD;

        return static_cast<int>(result);
    }
};
