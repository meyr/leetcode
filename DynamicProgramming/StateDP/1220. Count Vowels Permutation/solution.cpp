/*
 *  注意題目是 Each vowel 'a' may only be followed by an 'e'. 所以a之能跟在e 後面
 *  最後的結果是T的總和
 *
 */
class Solution {
    static constexpr int MOD = 1e9 + 7;
    using Matrix = vector<vector<int>>;
    Matrix multiply(const Matrix& A, const Matrix& B) {
        int sz = A.size();
        Matrix res(sz, vector<int>(sz));
        for(int y = 0; y < sz; ++y)
            for(int x = 0; x < sz; ++x)
                for(int k = 0; k < sz; ++k)
                    res[y][x] = (res[y][x] + 1LL * A[y][k] * B[k][x]) % MOD;
        return res;
    }
    Matrix powmod(Matrix& A, int exp) {
        int sz = A.size();
        Matrix res(sz, vector<int>(sz));
        for(int i = 0; i < sz; ++i)
            res[i][i] = 1;

        while(exp) {
            if(exp & 1) res = multiply(res, A);
            A = multiply(A, A);
            exp >>= 1;
        }
        return res;
    }
public:
    int countVowelPermutation(int n) {
        vector<vector<int>> T{
            {0, 1, 1, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 1, 0}
        };
        auto r = powmod(T, n - 1);
        int ans{};
        for(int y = 0; y < 5; ++y)
            for(int x = 0; x < 5; ++x)
                ans = (ans + r[y][x]) % MOD;
        return ans;
    }
};
