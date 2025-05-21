/*
    當沒有想法時，問問可不可以用binary search找答案?
    k 為 最小使matrix變成zero array, 如果越多queries越可能變成zero matrix

    k = 0, 1, 2, [3], 4, 5
    zm  x, x, x,  o, o, o


    time  : O((Q+N)logQ), N = sizeof(nums), Q = sizeof(queries)
    sapce : O(Q)
*/
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int sz = queries.size();
        int left = 0, right = sz + 1;
        while(left < right) {
            int mid = left + (right - left) / 2;
            unordered_map<int, int> m;
            for(int i = 0; i < mid; ++i) {
                vector<int>& q = queries[i];
                m[q[0]] += q[2];
                m[q[1] + 1] -= q[2];
            }
            bool rst{true};
            for(int i = 0, cur = 0; i < nums.size(); ++i) {
                cur += m[i];
                if(cur < nums[i]) {
                    rst = false;
                    break;
                }
            }
            if(rst) right = mid;
            else left = mid + 1;
        }
        return left == sz + 1 ? -1 : left;
    }
};
/*  參考解答 : https://leetcode.cn/problems/zero-array-transformation-ii/solutions/3674700/ling-shu-zu-bian-huan-ii-by-leetcode-sol-04r9/
 *  重點是怎麼跟新prefix sum, 一個queries[i] 會有left, right, 和value, 如果 index在left之前和right之後 那就沒影響
 *                                                                          index >= left and index <= right 那就必須加上value
 *
 *  time  : O(N+Q)
 */
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), sz = queries.size();
        vector<int> m(n + 1, 0);
        int k = 0;
        for (int i = 0, cur = 0; i < n; ++i) {
            int num = nums[i];
            cur += m[i];
            while (k < sz && cur < num) {
                vector<int>& q = queries[k];
                int left = q[0], right = q[1], val = q[2];
                m[left] += val;
                m[right + 1] -= val;
                if (left <= i && i <= right)                    // __important__ 必須更新cur 如果index在query範圍內
                    cur += val;
                k++;
            }
            if (cur < num) return -1;
        }
        return k;
    }
};
