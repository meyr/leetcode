/*  選取相鄰兩個乘於-1 --> 也就是可以把任兩個<0的值都轉正 或是把一個<0推到最小的那邊去
 *  Greedy point : 如果是偶數個負數都可以轉正 奇數個就會只剩下最後一個<0 把它推到最小那個
 *                 所以題目變成計算有幾個<0 和紀錄最小的數值即可。
 *
 *  time  : O(NM)
 *  space : O(1)
 */
class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long ans{};
        int cnt{}, minv{INT_MAX};
        for(auto& r : matrix) {
            for(auto& n : r) {
                cnt += n < 0;
                ans += abs(n);
                minv = min(minv, abs(n));
            }
        }
        return ans - (cnt & 1 ? minv << 1 : 0);
    }
};
/*
    -1, 0, -1
    -2, 1, 3
     3, 2, 2

    2, 9, 3
    5, 4, -4
    1, 7, 1

    1, 2, 3
    -1, -2, -3
    1, 2, 3

    --> 18 - 2 * 1
*/
