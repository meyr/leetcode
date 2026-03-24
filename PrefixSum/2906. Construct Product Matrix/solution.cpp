/*  如果數值不大 使用除法就可以解決
 *  但是數值太大又使用了mod 所以無法用除法來解決
 *
 *  不能用除法那就使用乘法
 *  prefix : (x, y) 左邊所有element相乘
 *  suffix : (x, y) 右邊所有element相乘
 *  forward: (x, y) 上面row的相乘
 *  backward:(x, y) 下面rowk的相乘
 *
 *  time  : O(MN + MN + M + M + MN) = O(MN)
 *  space : O(MN + MN + M + M + MN) = O(MN)
 */
class Solution {
    using ll = long long;
    int mod = 12345;
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> prefix(m, vector<int>(n + 1, 1)), suffix(m, vector<int>(n, 1));
        for(int y = 0; y < m; ++y) {
            for(int x = 1; x <= n; ++x) {
                prefix[y][x] = ((ll)prefix[y][x - 1] * grid[y][x - 1]) % mod;
            }
        }

        for(int y = 0; y < m; ++y) {
            for(int x = n - 2; x >= 0; --x) {
                suffix[y][x] = ((ll)suffix[y][x + 1] * grid[y][x + 1]) % mod;
            }
        }
        vector<int> forward(m, 1), backward(m, 1);
        for(int y = 1; y < m; ++y)
            forward[y] = ((ll)forward[y - 1] * prefix[y - 1].back()) % mod;

        for(int y = m - 2; y >= 0; --y)
            backward[y] = ((ll)backward[y + 1] * prefix[y + 1].back()) % mod;

        vector<vector<int>> rtn(m, vector<int>(n));
        for(int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                rtn[y][x] = ((ll)prefix[y][x] * suffix[y][x] * forward[y] * backward[y]) % mod;
            }
        }

        return rtn;
    }
};
/*  可以把mxn視為一個一維矩陣
 *
 *      x, x, x, y, y     o點的乘積就是, 所有x相乘*y相乘
 *      x, x, o, y, y
 *      x, x, y, y, y
 *
 */
class Solution {
public:
    static vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        const int N = 12345, n = grid.size(), m = grid[0].size();
        vector<vector<int>> ans(n, vector<int>(m));
        uint64_t pref = 1, suf = 1;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++){
                ans[i][j] = pref;
                pref = pref * grid[i][j] % N;
            }
        for(int i = n - 1; i >= 0; i--)
            for(int j = m - 1; j >= 0; j--){
                ans[i][j] = ans[i][j] * suf % N;
                suf = suf * grid[i][j] % N;
            }
        return ans;
    }
};
