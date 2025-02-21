/*  一開始很在意可以覆蓋的規則
 *  意味著 每次覆蓋我就需要修改floor 這樣會讓問題變複雜
 *  從Greedy的角度來看 覆蓋的越多越好 所以應該不要重疊才是最好的解
 *
 *  time  : O(NM) , N : size of floor, M : numCarpets
 *  space : O(NM)
 */
class Solution {
    int carpetLen;
    int helper(string& floor, int num, int idx) {
        if(num < 0) return 1e4;
        else if(idx >= floor.size()) return 0;
        else if(~mem[num][idx]) return mem[num][idx];
        int notused = helper(floor, num, idx + 1) + (floor[idx] == '1');
        int used = helper(floor, num - 1, idx + carpetLen);
        return mem[num][idx] = min(notused, used);
    }
    vector<vector<int>> mem;
public:
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        if(numCarpets * carpetLen >= floor.size()) return 0;
        this->carpetLen = carpetLen;
        mem.resize(numCarpets + 1, vector<int>(floor.size(), -1));
        return helper(floor, numCarpets, 0);
    }
};
/*
 *  參考解答:
 *  https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/solutions/1863967/memory-optimized-dp-by-votrubac-hc08/
 *
 *  概念差不多 多判斷了 floor.size() - i <= n * len 也就是剩下的carpets可以覆蓋剩下的tiles就回傳0
 *             還有如果tiles[i] == '0' 原本就是黑色直接不覆蓋     
 */
int dp[1001][1001] = {};
int dfs(string &floor, int i, int n, int len) {
    if (n < 0)
        return floor.size();
    if (floor.size() - i <= n * len)
        return 0;
    if (floor[i] == '0')
        return dfs(floor, i + 1, n, len);
    if (dp[i][n] == 0)
        dp[i][n] = 1 + min(1 + dfs(floor, i + 1, n, len), dfs(floor, i + len, n - 1, len));
    return dp[i][n] - 1;
}
// dfs(i, n) = f(dfs(i + 1, n), dfs(i + len, n - 1))
//                  <-----                    |
//                                            |
//                                           \|/
//
int minimumWhiteTiles(string floor, int numCarpets, int len) {
    return dfs(floor, 0, numCarpets, len);
}
/*  上面解法改成bottom up
 *
 */
int dp[1001][1001] = {};
int minimumWhiteTiles(string floor, int numCarpets, int len) {
    for (int i = floor.size() - 1; i >= 0; --i) {
        dp[i][0] = dp[i + 1][0] + (floor[i] == '1'); // black tiles 直接跳過
        for (int c = 1; c <= numCarpets; ++c)
            dp[i][c] = min(dp[i + 1][c] + (floor[i] == '1'), dp[min(1000, i + len)][c - 1]);   // min(1000, i + len) 避免超出array範圍
    }
    return dp[0][numCarpets];
}
