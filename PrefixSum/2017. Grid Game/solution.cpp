/*  因為grid只有兩列 所以當robot轉下去down 他就只能一直走right
 *  所以1st robot只有n個選擇 選擇轉下去的點
 *
 *  2nd robot只能從1st robot選剩下的選出最大值 只會有兩種可能
 *  一種是都選第0 row, 一種是都選1st row
 *
 *  time  : O(N)
 *  space : O(N)
 */
typedef long long ll;
class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        int sz = grid[0].size();
        vector<vector<long long>> llgrid(2, vector<long long>(sz)); 
        for(int y = 0; y < 2; ++y) {
            llgrid[y][0] = grid[y][0];
            for(int x = 1; x < sz; ++x)
                llgrid[y][x] = llgrid[y][x - 1] + grid[y][x];
        }
        
        ll ans{LLONG_MAX};
        for(int i = 0; i < sz; ++i) {
                ans = min(ans,                                    //         first  robot要把points最小化  
                            max(llgrid[0].back() - llgrid[0][i],  // 0-row   second robot要把points最大化
                                (i > 0 ? llgrid[1][i - 1] : 0))   // 1-row
                );
        }
        
        return ans;
    }
};
/*  參考解答
 *  https://leetcode.com/problems/grid-game/solutions/1486340/cjavapython-robot1-minimize-topsum-and-b-58dr/
 *
 *  想法一樣因為計算 2nd robot只需要統計 0-row後面累加 所以先使用accumulate把0-row total sum加起來
 *                                       1-row前面累加 只需要跟著for loop累加
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        long long topSum = accumulate(begin(grid[0]), end(grid[0]), 0LL), bottomSum = 0;
        long long ans = LLONG_MAX;
        for (int i = 0; i < grid[0].size(); ++i) {
            topSum -= grid[0][i];
            ans = min(ans, max(topSum, bottomSum));
            bottomSum += grid[1][i];
        }
        return ans;
    }
};
