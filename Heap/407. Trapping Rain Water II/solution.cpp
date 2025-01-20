/*  參考 : https://leetcode.cn/problems/trapping-rain-water-ii/solutions/1079738/jie-yu-shui-ii-by-leetcode-solution-vlj3/
 *
 *  principle:
 *  1. 周圍的方塊 不管高度為何 都無法儲水 因為水會往邊界流掉
 *  2. 水會往低的地方流 所以要儲水 __必須比周圍方塊還要低__
 *  
 *  solution:
 *  1.  從周圍最低的方塊向四周前進 遇到比自己高的 水一定會流掉 
 *  2.                             遇到比自己低的 水才會被保留
 *
 *  3.  因為使用minheap來依序處理 所以都會先處理到最低的方塊
 *
 *  complexity:
 *
 *  time : O(MNlogMN)
 *  space : O(MN)
 */
typedef pair<int,int> pii;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if (heightMap.size() <= 2 || heightMap[0].size() <= 2) {    // special case: 只有兩行或是兩列全部都是周邊block無法儲水
            return 0;
        }
        int m = heightMap.size();
        int n = heightMap[0].size();
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        vector<vector<bool>> visit(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {                               // 把周邊的block放入minheap 這些無法儲水 從周邊的block出發往內部走
            for (int j = 0; j < n; ++j) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    pq.push({heightMap[i][j], i * n + j});
                    visit[i][j] = true;
                }
            }
        }

        int res = 0;
        int dirs[] = {-1, 0, 1, 0, -1};
        while (!pq.empty()) {
            pii curr = pq.top();
            pq.pop();
            for (int k = 0; k < 4; ++k) {               // 探訪四周的block
                int nx = curr.second / n + dirs[k];
                int ny = curr.second % n + dirs[k + 1];
                if( nx >= 0 && nx < m && ny >= 0 && ny < n && !visit[nx][ny]) {
                    if (heightMap[nx][ny] < curr.first) {       // 下個block比目前的block還低 --> 可以儲水
                        res += curr.first - heightMap[nx][ny];
                    }
                    visit[nx][ny] = true;
                    pq.push({max(heightMap[nx][ny], curr.first), nx * n + ny}); // __important__ : 紀錄遇到最高的block 因為越往裡面走 可以儲水的高度會被最高block決定
                }
            }
        }

        return res;
    }
};
