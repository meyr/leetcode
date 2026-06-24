class Solution {
private:
    const int MOD = 1e9 + 7;
    using Matrix = vector<vector<long long>>;
    enum {
        down, up
    };
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
                T[id(x, up)][id(y, down)] = 1;
            }
            // 上升 -> 下降 (下一步的數 x 必須小於當前的數 y)
            for (int y = x + 1; y < m; y++) {
                T[id(x, down)][id(y, up)] = 1;
            }
        }

        // 4. 初始化長度為 2 的狀態向量 (start vector)
        vector<long long> start(states, 0);
        for (int a = 0; a < m; a++) {
            for (int b = 0; b < m; b++) {
                if (a == b) continue; // 不能相等
                if (a < b)  start[id(b, up)]++; // 遞增趨勢 (上升)
                else        start[id(b, down)]++; // 遞減趨勢 (下降)
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
