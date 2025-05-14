/*  參考 : https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/solutions/5982144/super-fast-45-ms-matrix-fast-power-by-vo-m78t/
 *
 */
class Solution {
    int mod = 1e9 + 7;
    class Matrix{
        int mod = 1e9 + 7;
        vector<vector<int>> _m;
    public:
        Matrix() : _m(26, vector<int>(26)) {}
        Matrix(vector<int>& nums) : Matrix() {
            for(int i = 0; i < 26; ++i)
                for(int j = 1; nums[i] && j <= nums[i]; ++j)
                    _m[i][(i + j) % 26] = 1;                            // __important__重點是定義Matrix代表從char i經過一次轉換後會變成多個char
        }                                                               //                                         矩陣相乘就是經過一次轉換
        auto &operator[](int idx) { return _m[idx]; }
        auto &operator[](int idx) const { return _m[idx]; }             // 因為input argument是const auto& other所以必須提供 const auto& operator[]() const 來存取matrix
        Matrix operator*(const auto& other) const {
            Matrix res;
            for(int i = 0; i < 26; ++i)
                for(int j = 0; j < 26; ++j)
                    for(int k = 0; k < 26; ++k)
                        res[i][j] = (res[i][j] + (long long)_m[i][k] * other[k][j]) % mod;
            return res;
        }
    };
    Matrix pow(Matrix& m, int t) {                                      // 經過t次轉換後的矩陣
        if(t == 1) return m;
        Matrix res = pow(m, t / 2);
        res = res * res;
        return t % 2 ? res * m : res;
    }
public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        Matrix m(nums);
        Matrix mp = pow(m, t);
        vector<int> cnt(26);
        for(int i = 0; i < 26; ++i)
            for(int j = 0; j < 26; ++j)
                cnt[i] = (cnt[i] + mp[i][j]) % mod;
        int ans{};
        for(auto& c : s)
            ans = (ans + cnt[c - 'a']) % mod;
        return ans;
    }
};
/*
    ex : nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]

    Matrix = [0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       <-- 'a' 轉成一個'b'        轉換矩陣 本來的initial state應該是[1,0,0,0,0...0]
              0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       <-- 'b' 轉成一個'c'                                          [0,1,0,0,0...0]
              0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       <-- 'c' 轉成一個'd'                                          ...
              ...                                                                                                                     [0,0,0,0,0...1] 

              1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]       <-- 'z' 轉成一個'a'一個'b'

    Matrix * Matrix =           

            [0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       <-- 'a' 轉成一個'c'
             0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       <-- 'b' 轉成一個'd'
             0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       <-- 'c' 轉成一個'e'
             ...
                                                                                                  
             0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]       <-- 'z' 轉成一個'b'一個'c'
*/
