/*  參考 : https://leetcode.com/problems/count-square-submatrices-with-all-ones/solutions/441306/java-c-python-dp-solution/
 *
 *  題目是要數有幾個正方形1x1, 2x2, 3x3...
 *  所以如果找出最大的正方形ex: 3x3 邊是3則裡面會有3個正方形1x1, 2x2, 和3x3
 *                                       1, 1, 1
 *                                       1, 1, 1
 *                                       1, 1, 1
 *
 *  所以找出每個(i, j)可以組成的最大正方形，會被A[i - 1][j], A[i][j - 1]和A[i - 1][j - 1]來決定
 *
 *  time  : O(NM)
 *  sapce : O(1)
 */
class Solution {
public:
    int countSquares(vector<vector<int>>& A) {
        int res = 0;
        for (int i = 0; i < A.size(); ++i)
            for (int j = 0; j < A[0].size(); j++) {
                if (A[i][j] && i && j) // __important__ i, j 一定要大於等於1 才會成立 且A[i][j]也要為1才需要判斷
                    A[i][j] += min({A[i - 1][j - 1], A[i - 1][j], A[i][j - 1]});
                res += A[i][j];
            }
        return res;
    }
};
