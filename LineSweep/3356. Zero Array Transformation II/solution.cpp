/*  參考解答 : https://leetcode.com/problems/zero-array-transformation-ii/solutions/6501391/zero-array-transformation-ii-by-leetcode-5waf/
 *  使用binary search
 * 
 *  time  : O((M+N)logN), N : size of nums
 *  space : O(N)
 */
class Solution {
    bool check(vector<int>& nums, vector<vector<int>>& q, int k) {
        int sz = nums.size();
        vector<int> dv(sz + 1); // __ important__ 之前都用map來存儲, 花點空間使用vector會更容易實作
        for(int i = 0; i < k; ++i) {
            dv[q[i][0]] += q[i][2];
            dv[q[i][1] + 1] -= q[i][2];
        }
        for(int i = 0, sum = 0; i < sz; ++i) {
            sum += dv[i];
            if(sum < nums[i]) return false;
        }
        return true;
    }
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int left = 0, right = queries.size();
        if(!check(nums, queries, right)) return -1;     // __important__ 先處理特例
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(check(nums, queries, mid)) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};
/* 單純使用line swipe
 * time  : O(N + M)
 * space : O(N)
 */
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int sz = nums.size(), qcnt = 0;                         // qcnt為使用queries的個數
        vector<int> differenceArray(sz + 1);                    // __important__ 一樣使用vector來儲存line swpie的數值
        for (int index = 0, sum = 0; index < sz; index++) {     // sum為目前的累加值
            while (sum + differenceArray[index] < nums[index]) {
                qcnt++;
                if (qcnt > queries.size())
                    return -1;

                int left = queries[qcnt - 1][0], right = queries[qcnt - 1][1],
                    val = queries[qcnt - 1][2];

                if (right >= index) { //     right >= index有以下兩種情況, 但是right < index呢?(while loop會往下一個表示之前的nums[i]已經滿足了, 所以不需要考慮right < idx)
                    differenceArray[max(left, index)] += val; // 如果index > left 表示 left < index < right --> 加入val
                                                              // 如果index < left 表示 index < left < right --> 目前index還未影響，先加到left
                    differenceArray[right + 1] -= val;
                }
            }
            sum += differenceArray[index];
        }
        return qcnt;
    }
};
