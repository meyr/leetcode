/*
 *  參考lee215解答 : https://leetcode.com/problems/count-ways-to-group-overlapping-ranges/solutions/3256371/java-c-python-sort-solution/
 *  想法和我的解法solution.cpp一樣 但是code更精簡
 *
 */
class Solution {
public:
    int countWays(vector<vector<int>>& ranges) {
        int res = 1, last = -1, mod = 1e9 + 7;
        sort(ranges.begin(), ranges.end());
        for (auto r: ranges) {
            if (last < r[0])
                res = res * 2 % mod;
            last = max(last, r[1]);
        }
        return res;
    }
};
