/*  參考解答
 *
 *  why line swep?
 *
 *  先考慮兩個數字 [a, b] 其中a <= b, 因為我們可以把兩個數取代成 [1, limit] 所以最小值是 2, 最大值是 limit * 2
 *                                    指取代一個 [1, b], [limit, b], [a, 1], [a, limit] 因為a < b 所以最小值是 a + 1, 最大值是 b + limit, range = [a + 1, b + limit]
 *
 *                                    我們把它畫出來
 *
 *                              op=2   ==========                            ===========
 *                              op=1             ============= ==============
 *                              op=0                          =
 *                                    -|---------+------------+------------+-----------|---------> target
 *                                     2        a + 1        a+b         b + limit    2*limit
 *
 *  每一個pair都可以化成三段線段 所以可以畫出以下圖
 *                                     ==========                            ===========  pair(nums[0], nums[sz - 0 - 1])
 *                                               ============= ==============
 *                                                            =
 *
 *                                     _______________                          ________  pair(nums[1], nums[sz - 1 - 1])
 *                                                    ____________ _____________
 *                                                                _
 *                                      ...
 *
 *                                     *******                   ***********************  pairs(nums[n], nums[sz - n - 1])
 *                                            ********* *********
 *                                                     *
 *                                    -|------------------------------------------------|---------> target
 *                                     2                                             2*limit
 *
 *  所以使用line swep來掃描哪個target會有最小值
 *
 *  time  : O(N + 2*L) = O(N + L)
 *  space : O(2*L)     = O(L)
 */

class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int sz = nums.size();
        vector<int> diff(2 * limit + 2);
        for (int i = 0; i < sz / 2; ++i) {
            int a = min(nums[i], nums[sz - i - 1]);
            int b = max(nums[i], nums[sz - i - 1]);
            // op = 2
            diff[2] += 2;
            diff[2 * limit + 1] -= 2;
            // op = 1
            diff[1 + a] -= 1;
            diff[b + limit + 1] += 1;
            // op = 0
            diff[a + b] -= 1;
            diff[a + b + 1] += 1;
        }
        int ans{sz * 2}, cur{};
        for(int i = 2; i <= 2 * limit; ++i) {
            cur += diff[i];
            ans = min(ans, cur);
        }
        return ans;
    }
};
