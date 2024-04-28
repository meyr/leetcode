/*   
 *   如果每個edge的weight == 1, 則找出到另一個node的最短路徑就是他的距離
 *   這樣可以解出來 但是TLE 因為time complexity : O(N^3)
 *
 */
class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> dp(n, vector<int>(n, 1e5));
        for(int i = 0; i < n; ++i) dp[i][i] = 0;
        for(auto& e : edges) {
            dp[e[0]][e[1]] = 1;
            dp[e[1]][e[0]] = 1;
        }
        for(int m = 0; m < n; ++m) {
            for(int x = 0; x < n; ++x) {
                for(int y = 0; y < n; ++y) {
                    if(x == m || y == m) continue;
                    if(dp[x][m] + dp[m][y] < dp[x][y])
                        dp[x][y] = dp[x][m] + dp[m][y];
                }
            }
        }
        vector<int> ans;
        for(int i = 0; i < n; ++i)
            ans.push_back(accumulate(begin(dp[i]), end(dp[i]), 0));
        return ans;
    }
};
/*
    0  1  2  3  4  5
 0  0  1  1 
 1  1  0
 2  1     0  1  1  1
 3        1  0
 4        1     0
 5        1        0       
*/
