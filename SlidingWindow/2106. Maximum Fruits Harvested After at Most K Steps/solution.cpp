/*  參考: https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/solutions/7037658/100-runtime-beat-optimal-maximum-fruits-6pjm1/
 *  
 *  為什麼可以用slinding window?
 *  因為答案一定是subarray, 因為從startPos往右走, 或是往左走, 或是一次轉折(先向左再向右, 或是先向右再向左)
 *  答案都會是在一個subarray之內, 所以可以用slinding window 
 *
 *  __slinding window大小就是從startPos出發, 可以在k內可以到達的範圍__
 *  因為有兩種走法(left->right, right->left) 所以選擇最少步數方式, 目的是可以走完這個slinding window當然是選最少的步數
 *
 *  如果startPos == left 則 minStep() --> min(right - left, right - left + right - left)
 *                                            只剩向右走距離     向右走再向左走, 就是2*(right - left)
 *
 *  如果startPos == right 則 minStep() --> min(right - left + right - left, right - left)
 *                                             向左走再向右走                只剩向左走的距離
 *
 *  如果startPos 在[left, right]中間 就一定要先向左走再向右 或是 先向右再向左 兩個選一個最佳距離
 */
class Solution {
    int minStep(int left, int right, int start) {
        return min(
            abs(start - left) + (right - left),     // __why abs()?__, 因為可能出現 startPos, left, right  或是 left, right, startPos
            abs(right - start) + (right - left)     //                 這會造成 start-left < 0 或是 right - start < 0            
        );
    }
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int ans{}, sum{};
        for(int left = 0, right = 0; right < fruits.size(); ++right) {
            sum += fruits[right][1];
            while(left <= right && minStep(fruits[left][0], fruits[right][0], startPos) > k) {
                sum -= fruits[left][1];
                left++;
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};
