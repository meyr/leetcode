class Solution {
    int m, n;
    long long INF = 1e16;
    vector<vector<vector<long long>>> mem;

    long long helper(const vector<vector<int>>& coins, int y, int x, int k) {
        if (y < 0 || x < 0) return -INF;
        if (mem[y][x][k] != -1e18) return mem[y][x][k];

        if (y == 0 && x == 0) {
            long long res = coins[y][x];
            if (k > 0 && coins[y][x] < 0) res = 0; // 起點也可以選抵銷
            return mem[y][x][k] = res;
        }


        long long res = max(helper(coins, y - 1, x, k), helper(coins, y, x - 1, k)) + coins[y][x];
        if (k > 0 && coins[y][x] < 0) { // 只有n > 0 且是負值才需要使用
            res = max({res,
                       helper(coins, y - 1, x, k - 1),
                       helper(coins, y, x - 1, k - 1)});
        }

        return mem[y][x][k] = res;
    }

public:
    int maximumAmount(vector<vector<int>>& coins) {
        m = coins.size();
        n = coins[0].size();
        mem.assign(m, vector<vector<long long>>(n, vector<long long>(3, -1e18)));   // 因為有負值所以不能用-1 要改用負較小的值
        return (int)helper(coins, m - 1, n - 1, 2);
    }
};
