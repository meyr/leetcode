/*
    一開始使用BFS結果TLE
    想法是把y, x 和機率都存在queue

     k = 2         k = 1          k = 0
      
    1  *  *      *  *    *     2/64  *  1/64
    *  *  *      *  *   1/8    *     *   *
    *  *  *      *  1/8  *     1/64  *   *

                                                ans = 2/64 + 1/64 + 1/64
*/

class Solution {
    vector<vector<int>> dirs{{ 1,  2}, { 2,  1}, 
                             {-1,  2}, {-2,  1}, 
                             {-1, -2}, {-2, -1}, 
                             { 1, -2}, { 2, -1}};
public:
    double knightProbability(int n, int k, int row, int column) {
        if(k == 0) return 1.0;
        queue<tuple<int, int, double>> q;
        q.push({row, column, 1.0});
        while(k) {
            for(int loop = q.size(); loop > 0; --loop) {
                auto [y, x, v] = q.front(); q.pop();
                for(auto& d : dirs) {
                    int ny = y + d[0];
                    int nx = x + d[1];
                    if(ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
                    q.push({ny, nx, v / 8.0});
                }
            }
            k--;   
        }

        double ans{};
        while(!q.empty()) {
            ans += get<2>(q.front());
            q.pop();
        }
        
        return ans;
    }
};
/*
    參考解答使用dynamic programming
    在(y, x)上還剩多少step(k) 結果是固定的 所以不用重複計算。

    time  : O(KN^2)
    space : O(KN^2)
*/
class Solution {
    int n;
    vector<vector<vector<double>>> dp;
    vector<vector<int>> dirs{{ 1,  2}, { 2,  1}, 
                             {-1,  2}, {-2,  1}, 
                             {-1, -2}, {-2, -1}, 
                             { 1, -2}, { 2, -1}};

    bool isInBoard(int y, int x) {
        if(y < 0 || x < 0 || y >= n || x >= n) return false;
        else return true;
    }
    double helper(int y, int x, int k) {
        if(k == 0) return 1;
        if(dp[k][y][x] != -1.0) return dp[k][y][x];
        double ans = 0.0;
        for(auto& d : dirs) {
            int ny = y + d[0];
            int nx = x + d[1];
            if(isInBoard(ny, nx)) {
                ans += helper(ny, nx, k - 1) / 8.0;
            }
        }
        return dp[k][y][x] = ans;
    }
public:
    double knightProbability(int n, int k, int row, int column) {
        this->n = n;
        dp.resize(k + 1, vector<vector<double>>(n, vector<double>(n, -1.0)));
        return helper(row, column, k);
    }
};
