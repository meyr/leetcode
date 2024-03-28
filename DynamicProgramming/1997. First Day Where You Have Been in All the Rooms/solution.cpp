/*
 *   參考解答 : https://leetcode.com/problems/first-day-where-you-have-been-in-all-the-rooms/solutions/1445225/python-short-dp-explained/
 *
 *   為了到達index 必須先到達index - 1 兩次 2 * helper(nextVisit, idx - 1)
 *   但是第二次只需要從 nextVisit[idx - 1] 到 idx - 1 
 *   所以必須減掉 從0到nextVisit[idx - 1]即為helper(nextVisit, nextVisit[idx - 1]) 
 *
 *   time complexity  : O(N)
 *   space complexity : O(N) 
 */

class Solution {
    int mod = 1e9 + 7;
    int helper(vector<int>& nextVisit, int idx) {
        if(~mem[idx]) return mem[idx];
        else return mem[idx] =
            (2 * (long)helper(nextVisit, idx - 1) - helper(nextVisit, nextVisit[idx - 1]) + 2 + mod) % mod;
    }
    vector<int> mem;
public:
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
        int sz = nextVisit.size();
        // top bottom, memorization
        //mem.resize(sz, -1);
        //mem[0] = 0;
        //return helper(nextVisit, sz - 1);

        // bottom up, tabulation
        vector<int> dp(sz);
        dp[0] = 0;
        for(int i = 1; i < sz; ++i)
            dp[i] = ((long)dp[i - 1] * 2 + 2 + mod - dp[nextVisit[i - 1]]) % mod;

        return dp.back();
    }
};
