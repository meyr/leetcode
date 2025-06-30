/* subsequence 的問題都可以先排序 這樣只需要考慮從小到大的case
 * 題目要求max num + min num <= target, 暴力破解就是使用兩個for loop, 但是 size(nums) = 1e5 所以會TLE
 * 問題變成在排序過後的數列中 找出兩個數的合小於等於target
 *
 * ex: [1, 2, 3, 4], target = 6     基本上必須使兩個for loop 掃描兩個數的組合  for(int i = 0; i < sz; ++i)
 *                                                                                 for(int j = i; j < sz; ++j)
 * 1+1=2, 1+2=3, 1+3=4, 1+4=5
 *        2+2=4, 2+3=5, 2+4=6
 *               3+3=6, 3+4=7
 *                      4+4=8
 *
 * 所有的可能是 2, 3, 4, 5    --->  越來越大  |
 *                 4, 5, 6                    |
 *                    6, 7                    |
 *                       8                   \|/   越來越大(比target大就先往下找)
 *
 *
 *  一開始在  2, 3, 4, 5(*)    2, 3, 4, 5     <= target繼續向下   2, 3, 4, 5      超過了向左找  2, 3, 4,    5
 *               4, 5, 6          4, 5, 6(*)                         4, 5, 6                       4, 5,    6
 *                  6, 7             6, 7                               6, 7(*)                       6(*), 7
 *                     8                8                                  8                                8
 *
 *  powmod(2, right - left)是因為
 *
 * 0, 1, 2
 *    x  x
 * 3, 5, 6 --> right - left = 2 --> pow(2, right - left) = 4
 * 第一個3一定要選,最後兩個可以有取或是不取的選擇  [3]   [3, 5][3, 6]  [3, 5, 6]
 *                                               都不選     選一個      兩個都選
 *
 * 如果不固定一個, 會有重複的情況, 上面的情況是2^3, 下次選到5也會有重複的情況
 *
 *  time  : O(NlogN + N) = O(NlogN)
 *  space : O(logN)
 */
class Solution {
    int powmod(int b, int e, int m = 1e9 + 7) {
        if(b == 1 || e == 0) return 1;
        else if(e == 1) return b;
        else {
            long long rtn = powmod(b, e / 2, m);
            rtn = (rtn * rtn) % m;
            return e % 2 ? (rtn * b) % m : rtn;
        }
    }
public:
    int numSubseq(vector<int>& nums, int target) {
        sort(begin(nums), end(nums));
        int left = 0, right = nums.size() - 1, ans{}, mod = 1e9 + 7;
        while(left <= right) {
            int sum = nums[left] + nums[right];
            if(sum > target) right--;
            else {
                ans = (ans + powmod(2, right - left)) % mod;
                left++;
            }
        }
        return ans;
    }
};
