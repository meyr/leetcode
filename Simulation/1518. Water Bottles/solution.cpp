/*  模擬喝水狀態
 *
 *  1. 先將空瓶換成水
 *  2. 喝掉所有的水
 *  3. 計算剩下的空瓶
 *
 *  numBottles : 有水的瓶子
 *  empty      : 沒水的空瓶
 */

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int ans{}, empty{};
        while(numBottles || empty >= numExchange) {
            // 1. 
            numBottles += empty / numExchange;
            empty %= numExchange;
            // 2.
            ans += numBottles;
            // 3
            empty += numBottles;
            numBottles = 0;
        }
        return ans;
    }
};
