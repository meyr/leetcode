/*  ref : https://leetcode.com/problems/delete-columns-to-make-sorted-ii/solutions/203171/c-12-ms-brute-force-by-votrubac-c7nv/
 *
 *  兩兩相比 (1)只要找到一個A[i - 1][j]  > A[i][j] 就必須刪掉放入di裡面
 *           (2)如果找到    A[i - 1][j] == A[i][j] 就繼續往下比
 *           (3)如果找到    A[i - 1][j]  < A[i][j] 這兩個字串就不用比了 因為已經是lexicographic order就選下一組繼續比
 */
 class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        unordered_set<int> di;
        for (auto i = 1; i < A.size(); ++i) {
            for (auto j = 0; j < A[i].size(); ++j) {
                if (di.count(j) > 0 || A[i - 1][j] == A[i][j]) continue;    // (2) 或是這個column已經刪掉就繼續往下比
                if (A[i - 1][j] > A[i][j]) {                                // (1) 刪掉此column重新開始比
                    di.insert(j);
                    i = 0;  // 重新開始比
                }
                break;                                                      // (3) 不用繼續比了 往下一組
            }
        }
        return di.size();
    }
};
