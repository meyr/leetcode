/* ref : https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/solutions/6075890/javacpython-dp-first-child-go-diagonal-b-osof/
 *
 *  time  : O(N^2 + N + N^2 + N^2) = O(N^2)
 *  space : O(1)
 */
class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& A) {
        int n = A.size();
        // Set inaccessible cells to 0
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                if (y < x && x < n - 1 - y) {   // 上半部, second child from(0, n - 1)
                    A[y][x] = 0;
                }
                if (x < y && y < n - 1 - x) {   // 下半部, second child from(n - 1, 0)
                    A[y][x] = 0;
                }
            }
        }
        // First child
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += A[i][i];
        }
        // Second child
        for (int y = 1; y < n; ++y) {
            for (int x = y + 1; x < n; ++x) { // x = y + 1對角線之後
                A[y][x] += max({A[y - 1][x - 1], A[y - 1][x], (x + 1 < n) ? A[y - 1][x + 1] : 0});  // 從上面三個方向過來的
            }
        }
        // Thrid child
        for (int x = 1; x < n; ++x) {
            for (int y = x + 1; y < n; ++y) { // y = x + 1 對角線之後
                A[y][x] += max({A[y - 1][x - 1], A[y][x - 1], (y + 1 < n) ? A[y + 1][x - 1] : 0});// 從左邊三個方向過來的
            }
        }
        return res + A[n - 1][n - 2] + A[n - 2][n - 1];  // A[n-1][n-1]是從他的上面和左邊過來 所以是A[n-1][n-2] A[n-2][n-1]
                                                         //            斜對角過來的A[n-2][n-2]是child1必經道路 已經收集過了
    }
};
