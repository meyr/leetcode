/*
 *  參考: https://leetcode.com/problems/maximum-elegance-of-a-k-length-subsequence/solutions/3869920/java-c-python-sort-by-profit/
 *
 *  time  : O(NlogN)
 *  space : O(N)
 */

class Solution {
public:
    long long findMaximumElegance(vector<vector<int>>& A, int k) {
        sort(A.begin(), A.end(), [](const vector<int>& a, const vector<int>& b) { // 先針對profit排序 高->低
            return a[0] > b[0];
        });
        long long res = 0, cur = 0;
        vector<int> dup;
        unordered_set<int> seen;
        for (int i = 0; i < A.size(); ++i) {
            if (i < k) {    // 前k個一律放進來 因為越多越好
                if (seen.count(A[i][1]))    // 如果這個category有用過 就把profit存起來 
                    dup.push_back(A[i][0]);
                cur += A[i][0];
            } else if (seen.find(A[i][1]) == seen.end()) { // 沒看過的category 表示有機會得到更大的res
                                                           // 看過的category不用處理 因為profit一定比之前的還小 size也不會增加
                if (dup.empty()) break; // 所有的組合中沒有重複的category 直接離開不用在比了 因為profit和size都是最大
                cur += A[i][0] - dup.back();    // 因為已經排序過profit 所以dup也是按照大到小排序 所以直接丟掉重複的category中最小的
                dup.pop_back();
            }
            seen.insert(A[i][1]);
            res = max(res, cur + (long long)pow(seen.size(), 2));
        }
        return res;
    }
};
