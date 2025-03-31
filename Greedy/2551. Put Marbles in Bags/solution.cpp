/*  參考解答 : https://leetcode.com/problems/put-marbles-in-bags/solutions/3111736/javacpython-3-approachs-best-on-by-lee21-ag8d/
 *
 *  因為分成k個group 則sum為
 *  (A[0] + A[i1]) + (A[i2] + A[i3]) +..... + (A[ik+1] + A[n-1])
 *  除了前後兩個 可以寫成
 *  A[0] + (A[i1] + A[i1+1]) + (A[i2] + A[i2+1]) + ... + (A[ik] + A[ik+1]) + A[n-1]
 *        -----------------    ----------------          -----------------
 *
 *  maximum - minimun 之後 A[0] 和 A[n-1] 會被扣掉
 *  所以只剩中間那些pair
 *
 *  time : O(N + NlogN + K) = O(NlogN + K) 因為k <= N 所以 O(NlogN)
 *  space : O(logN) 
 */
class Solution {
public:
    long long putMarbles(vector<int> A, int k) {
        long long res = 0, n  = A.size() - 1;
        for (int i = 0; i < n; ++i)
            A[i] += A[i + 1];               // 兩兩相加
        A.pop_back();                       // 最後一個element沒加入
        sort(A.begin(), A.end());           // Greedy point 從最大score的分割開始取
        for (int i = 0; i < k - 1; ++i)     // 因為maximum是取最後k個，minimum會出現在最前面k個
            res += A[n - 1 - i] - A[i];     // 所以 res += A[n - 1 - i] - A[i]
        return res;                         //              取maximum    取minimum
    }
};
/*  一開始以為是DP問題 但是寫出來MLE
 *
 */
class Solution {
    vector<long long> pfs;
    vector<vector<long long>> mem, mem2;
    long long helper(vector<int>& w, int k, int idx) {
        int remain = w.size() - idx;
        long long rtn = 0;
        if(~mem[k][idx]) return mem[k][idx];
        else if(idx >= w.size()) return 0;
        else if(k == 1) {
            rtn = w[idx]  + w.back();
        } else if(remain == k) {
            if(idx - 1 < 0) rtn = pfs.back() * 2;
            else rtn = (pfs.back() - pfs[idx - 1]) * 2;
        } else {
            for(int j = idx, r = remain; j < w.size() && r >= k; ++j, --r) {
                rtn = max(rtn, w[idx] + w[j] + helper(w, k - 1, j + 1));
            }
        }
        return mem[k][idx] = rtn;
    }
    long long helper2(vector<int>& w, int k, int idx) {
        int remain = w.size() - idx;
        long long rtn = LLONG_MAX;
        if(~mem2[k][idx]) return mem2[k][idx];
        else if(idx >= w.size()) rtn = LLONG_MAX;
        else if(k == 1) {
            rtn = w[idx]  + w.back();
        } else if(remain == k) {
            if(idx - 1 < 0) rtn = pfs.back() * 2;
            else rtn = (pfs.back() - pfs[idx - 1]) * 2;
        } else {
            for(int j = idx, r = remain; j < w.size() && r >= k; ++j, --r) {
                long long ans = helper2(w, k - 1, j + 1);
                rtn = min(rtn, w[idx] + w[j] + ans);
            }
        }
        return mem2[k][idx] = rtn;
    }
public:
    long long putMarbles(vector<int>& weights, int k) {
        int sz = weights.size();
        pfs.resize(sz);
        partial_sum(begin(weights), end(weights), begin(pfs));
        mem.resize(k + 1, vector<long long>(sz + 1, -1));
        mem2.resize(k + 1, vector<long long>(sz + 1, -1));
        return helper(weights, k, 0) - helper2(weights, k, 0);
    }
};
/*
    1, 3, 5, 1    k = 2
    [1][3, 5, 1]    (1+1) + (3+1) = 6
    [1, 3][5, 1]    (1+3) + (5+1) = 10
    [1, 3, 5][1]    (1+5) + (1+1) = 8

    idx = 0
    0, 1, 2, 3
    1, 3, 5, 1
    *j
    *  j
    *     j
*/
