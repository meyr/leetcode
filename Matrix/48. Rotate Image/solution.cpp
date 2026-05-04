/*  (y, x) -> (x, n - y - 1)
 *  再一次帶入
 *  (x, n - y - 1) -> (n - y - 1, n - x - 1)
 *  再一次帶入
 *  (n - y - 1, n - x - 1) -> (n - x - 1, y)
 *  再一次帶入
 *  (n - x - 1, y) -> (y, x)
 *
 *  time  : O(N^2 / 4) 因為一次轉四個element
 *  space : O(1)
 */
 Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int y = 0; y < n / 2; ++y) {
            for(int x = y; x  < n - y - 1; ++x) {
                int tmp = matrix[y][x];
                matrix[y][x] = matrix[n - x - 1][y];
                matrix[n - x - 1][y] = matrix[n - y - 1][n - x - 1];
                matrix[n - y - 1][n - x - 1] = matrix[x][n - y - 1];
                matrix[x][n - y - 1] = tmp;
            }
        }
    }
};
/*  參考其他解答
 *
 *
 */
class Solution {
public:
    void rotate(vector<vector<int>>& m) {
        int n = m.size();
        reverse(begin(m), end(m));
        for(int y = 0; y < n; ++y)  // y = 0, 1, 2
            for(int x = y + 1; x < n; ++x) // y = 0, x = 1, 2
                swap(m[y][x], m[x][y]);    // y = 1, x = 2
    }
};
/*
    1, 2, 3  --> reverse()    7, 8, 9
    4, 5, 6                   4, 5, 6
    7, 8, 9                   1, 2, 3


    y = 0, x = 1, 2

     7, (8), [9]   -->   7, 4, 1
    (4), 5 ,  6          8, 5, 6
    [1], 2,  3           9, 2, 3

    y = 1, x = 2

    7,  4 ,  1   -->     7, 4, 1
    8,  5 , (6)          8, 5, 2
    9, (2),  3           9, 6, 3

*/
