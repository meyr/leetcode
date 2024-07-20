/*
 * 想法是先把第一個column填上rowSum
 * 之後在根據colSum把資料一直往後面推
 *
 * time  : O(M + MN)
 * space : O(MN)
 */
class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        int m = rowSum.size(), n = colSum.size();
        vector<vector<int>> rtn(m, vector<int>(n));
        for(int i = 0; i < m; ++i)
            rtn[i][0] = rowSum[i];
        for(int i = 0; i < n - 1; ++i) {
            for(int j = 0; j < m; ++j) {
                int left = min(rtn[j][i], colSum[i]);
                colSum[i] -= left;
                rtn[j][i + 1] += rtn[j][i] - left;
                rtn[j][i] = left;
            }
        }
        return rtn;
    }
};
/*

     8,  6, 8

  5  5,  0, 0
  7  3,  4, 0
 10  0,  2, 8

*/
/*  參考解答：
 *  https://leetcode.cn/problems/find-valid-matrix-given-row-and-column-sums/solutions/2165784/gei-ding-xing-he-lie-de-he-qiu-ke-xing-j-u8dj/
 *
 *  time  : O(MN)
 *  space : O(MN)
 */
class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        int m = rowSum.size(), n = colSum.size();
        vector<vector<int>> rtn(m, vector<int>(n));
        int x = 0, y = 0;
        while(x < n && y < m) {
            int v = min(rowSum[y], colSum[x]);
            rtn[y][x] = v;
            rowSum[y] -= v;
            colSum[x] -= v;
            if(rowSum[y] == 0) y++;
            else x++;
        }
        return rtn;
    }
};
