/*  一開始使用暴力破解
 *
 *   time  : O(N^2)
 *   space : O(N)
 */
class Solution {
public:
    vector<int> minOperations(string boxes) {
        int sz = boxes.size();
        vector<int> ans(sz);
        for(int i = 0; i < sz; ++i) {
            for(int j = 0; j < sz; ++j)
                ans[i] +=  abs(j - i) * (boxes[j] - '0');
        }
        return ans;
    }
};
/*  後來發現其實可以拆解成左半邊和右半邊計算
 *
 *  time  : O(N)
 *  space : O(N)
 *  
 */
class Solution {
public:
    vector<int> minOperations(string boxes) {
        int sz = boxes.size();
        vector<int> left(sz);
        for(int i = sz - 2, cnt = boxes.back() == '1'; i >= 0; --i) {
            left[i] = left[i + 1] + cnt;
            cnt += boxes[i] == '1';
        }
        vector<int> right(sz);
        for(int i = 1, cnt = boxes.front() == '1'; i < sz; ++i) {
            right[i] = right[i - 1] + cnt;
            cnt += boxes[i] == '1';
            left[i] += right[i];
        }
        return left;
    }
};

/*
    0, 1, 2, 3, 4, 5
    0, 0, 1, 0, 1, 1
                   0
                1 = m[5]
             3 = m[5] * 2 + m[4] = left[4] + (m[4] + m[5])
          5 = m[5] * 3 + m[4] * 2 = (m[5] * 2 + m[4]) + (m[5] + m[4]) = left[3] + (m[5] + m[4])
       1+3+4 = 8 = left[2] + 3 = 8
*/


