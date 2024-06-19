/*
 * 參考lee215大神解答 : 
 * https://leetcode.com/problems/maximum-strictly-increasing-cells-in-a-matrix/solutions/3570296/java-c-python-dp-solution/
 *
 * 感念都差不多 但是可以做得更精簡
 * 
 * 1. 首先是 strictly increasing因為要找出比自己還大的數字 但是不等於自己
 *    所以使用 map<int, vector<int>> A; //value, position 
 *    每次指處理相同value的position這樣就可以跳過相同的狀況
 *
 * 2. 把比較完的先放在dp[i][j], 等相同value都處理完了再update vector<int> res
 *    這邊的res把row放在前面 把column放在後面 可以同時比較
 *
 * time  : O(MNlogMN + MN) = O(MNlogMN)
 * space : O(MN + MN + M + N) = O(MN)
 */

class Solution {
public:
    int maxIncreasingCells(vector<vector<int>>& M) {
        int m = M.size(), n = M[0].size();
        map<int, vector<int>> A; // O(MNlogMN)
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                A[M[i][j]].push_back(i * n + j);
        vector<vector<int>> dp(m, vector<int>(n, 0));
        vector<int> res(n + m, 0);
        for (auto& [a, pos] : A) { // O(MN)
            for (int p : pos) {
                int i = p / n, j = p % n;
                dp[i][j] = max(res[i], res[m + j]) + 1;
            }
            for (int p : pos) {
                int i = p / n, j = p % n;
                res[m + j] = max(res[m + j], dp[i][j]);
                res[i] = max(res[i], dp[i][j]);
            }
        }
        return *max_element(res.begin(), res.end());
    }
};
