/*
 *  參考 : https://leetcode.com/problems/student-attendance-record-ii/solutions/650804/evolve-from-brute-force-to-optimal/
 *
 */

class Solution {
    int n;
    // index, A 的數目, 連續L的數目
    int helper(int i, int A, int L) {
        if(i == n) return 1;
        if(~mem[i][A][L]) return mem[i][A][L];
        long res = helper(i + 1, A, 0); // P
        if(A == 0) res += helper(i + 1, 1, 0); // A
        if(L < 2) res += helper(i + 1, A, L + 1); // L
        return mem[i][A][L] = res % (int)(1e9 + 7);
    }
    vector<vector<vector<int>>> mem;
public:
    int checkRecord(int n) {
        mem.resize(n, vector<vector<int>>(2, vector<int>(3, -1)));
        this->n = n;
        return helper(0, 0, 0);
    }
};
