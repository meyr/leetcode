/*  參考gemini解答
 *
 *  這題的重點是遊戲方法
 *  因為每次加起來的數都要放回陣列最左邊
 *
 *  alice 第一次選 可以選到的就是prefix sum
 *  換bob選 因為alice選到的會放在 最左邊所以bob也是從這個值開始
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();

        // 1. 計算前綴和（直接複用 stones 陣列來省去額外空間）
        for (int i = 1; i < n; ++i) {
            stones[i] += stones[i - 1];
        }

        // 2. 從右向左維護 dp 值
        // res 代表當前能取得的最大分數差，初始從最後一個狀態 S[n-1] 開始
        int res = stones[n - 1];

        // 從倒數第二個元素往前推回至索引 1
        for (int i = n - 2; i >= 1; --i) {
            res = std::max(res, stones[i] - res);
                              //^^^^^^^^^          alice 選前i個可以得到的分數
                              //            ^^^^   因為bob可以得到alice之前選的分數 對 bob來說當然是選 i 之後的最大值 所以是res
                              // 兩個相減就是答案
        }

        return res;
    }
};
