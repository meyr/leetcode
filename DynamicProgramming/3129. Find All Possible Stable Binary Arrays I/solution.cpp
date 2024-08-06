/*
 *  根據題意寫以下code結果TLE
 *  這邊先統計前一個 ch 為0或是1, 然後在幾計算連續幾個ch也就是cnt變數
 *  但是變數太多為4D DP所以TLE
 *
 *  time : O(2NML) = O(NML)
 */
class Solution {
    int limit;
    int helper(int zero, int one, int ch, int cnt) {
        int rtn{};
        if(cnt > limit) return 0;
        else if(zero == 0 && one == 0) rtn = 1;
        else {
            if(zero)
                rtn = rtn + helper(zero - 1, one, 0, ch == 0 ? cnt + 1 : 1);
            if(one)
                rtn = rtn + helper(zero, one - 1, 1, ch == 1 ? cnt + 1 : 1);
        }
        return mem[zero][one][ch][cnt] = rtn;
    }
    vector<vector<vector<vector<int>>>> mem;
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        this->limit = limit;
        mem.resize(zero + 1, vector<vector<vector<int>>>(one + 1, vector<vector<int>>(2, vector<int>(limit + 1, -1))));
        return helper(zero, one, 0, 0);
    }
};
/*
 *  參考解答 : https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/solutions/5080679/c-3d-dp-memoisation-109ms-7-99mb/
 *  
 *  因為subarray.size() > limit 裡面一定要有0和1也就是
 *  subarray.size() <= limit 可以有連續的0或是1
 *
 *  假設limit = 3 則 [0][00][000][1][11][111] 均為合理, 根據前面是0/1 加上相反的subarray就可以保證subarray.size() <= limit不會有連續的0/1
 *
 *  [0]    -> [0][1], [0][11], [0][111]   
 *  [00]   -> [00][1], [00][11], [00][111]
 *  [000]  -> [000][1], [000][11], [000][111]
 *  [1]    -> [1][0], [1][00], [1][000]
 *  [11]   -> [11][0], [11][00], [111][000]
 *  [111]  -> [111][0], [111][00], [111][000]
 *
 *  time  : O(2NM) = O(NM)
 *
 */
class Solution {
    int memo[2][201][201], lmt;
    int mod = 1e9 + 7;
    long long dfs(int prev, int zeroes, int ones) {
        if (memo[prev][zeroes][ones] != -1) 
            return memo[prev][zeroes][ones];
        long long subRes = 0;
        if (prev) { // 前一個是1 所以加上所有0的subarray
            for (int i = 1; i <= min(lmt, zeroes); i++) 
                subRes += dfs(0, zeroes - i, ones);
        } else {  // 前一個是0 所以加上所以1的subarray
            for (int i = 1; i <= min(lmt, ones); i++) 
                subRes += dfs(1, zeroes, ones - i);
        }
        return memo[prev][zeroes][ones] = subRes % mod;
    }
public:
    int numberOfStableArrays(int zeroes, int ones, int limit) {
        long long res = 0;
        memset(memo, -1, sizeof(memo));
        memo[0][0][0] = memo[1][0][0] = 1;
        lmt = limit;
        for (int i = 1; i <= min(lmt, zeroes); i++) 
            res += dfs(0, zeroes - i, ones);
        for (int i = 1; i <= min(lmt, ones); i++) 
            res += dfs(1, zeroes, ones - i);
        return res % mod;
    }
};
