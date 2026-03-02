/*  ref : 參考官方解答
 *
 *  問題在如何得到最小的交換次數
 *  Greedy point : 第i row只需要往下找到第一個剛好滿足 pos[j] <= i 即可, pos[j] 最右邊第一個出現1的位置
 *
 *  找到k之後就必須模擬swap的過程 因為vector無法像list一樣操作, 但是還是建議使用vector
 *  + vector 的資料在記憶體中是連續儲存的, list 是由節點 (Node) 組成的，散落在記憶體各處。
 *  + vector 支援隨機存取 (operator[])，時間複雜度 O(1)。list 必須從頭遍歷 (std::advance 或 next)，時間複雜度 O(N)。
 *
 *  time  : O(N^2 + N^2) = O(N^2)
 *  space : O(N)
 */
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> pos(n, -1);
        for (int i = 0; i < n; ++i) {
            for (int j = n - 1; j >= 0; --j) {
                if (grid[i][j] == 1) {
                    pos[i] = j;         // 紀錄該行最右邊 1 的位置
                    break;
                }
            }
        }
        // 只要第i row的 最右邊 1 的位置 小於等於 i 就可以滿足
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int k = -1;                     // 是否有找到
            for (int j = i; j < n; ++j) {
                if (pos[j] <= i) {
                    ans += j - i;
                    k = j;
                    break;
                }
            }
            if (~k) {   // 找到了模擬swap
                for (int j = k; j > i; --j) {
                    swap(pos[j], pos[j - 1]);
                }
            } else
                return -1;
        }
        return ans;
    }
};
