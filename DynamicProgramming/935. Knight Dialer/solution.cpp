/*
 *  使用DP來計算
 *
 *  time  : O(N*10) = O(N)
 *  space : O(N*12) = O(N) 
 */
class Solution {
    int mod = 1e9 + 7;
    vector<vector<int>> dirs{{2, 1}, {1, 2},
                             {2, -1}, {1, -2},
                             {-2, 1}, {-1, 2},
                             {-2, -1}, {-1, -2}};
    int helper(int y, int x, int n) {
        if(n == 0) return 1;
        if(~mem[y * 3 + x][n]) return mem[y * 3 + x][n];
        int rtn{};
        for(auto& d : dirs) {
            int ny = y + d[0];
            int nx = x + d[1];
            if((ny >= 0 && nx >= 0 && ny < 3 && nx < 3) || (ny == 3 && nx == 1)) {
                rtn = (rtn + helper(ny, nx, n - 1)) % mod;
            }
        }
        return mem[y * 3 + x][n] = rtn;
    }
    vector<vector<int>> mem;
public:
    int knightDialer(int n) {
        int ans{};
        mem.resize(12, vector<int>(n, -1));
        for(int y = 0; y < 3; ++y)
            for(int x = 0; x < 3; ++x)
                ans = (ans + helper(y, x, n - 1)) % mod;
        ans = (ans + helper(3, 1, n - 1)) % mod;
        return ans;
    }
};
