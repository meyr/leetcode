/*  ref : https://leetcode.com/problems/maximum-running-time-of-n-computers/solutions/1693347/heap-vs-binary-search-by-votrubac-18l0/
 *
 *  why binary search? 
 *  因為答案有一致姓 如果答案m可以   則m - 1, m - 2一定也可以
 *                   如果答案m不可以 則m + 1, m + 2也一定不可以
 *
 *   time : 1, 2, [3], 4, 5   --> 所以答案是t = 3
 *   check: o  o   o   x  x
 *
 *
 */
class Solution {
    using ll = long long;
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        int sz = batteries.size();
        ll total = accumulate(begin(batteries), end(batteries), 0LL);
        if(n == 1) return total;
        if(n > sz) return 0;
        ll left = 0, right = total / n + 1, ans{};  // 因為total / n 有可能是答案，所以要 total / n + 1
        while (left < right) {
            long long m = left + (right - left) / 2, minutes = 0;
            for (auto& b : batteries)               // why this work?
                minutes += min((long long)b, m);    // 我們的目的是提供m的電力給電腦, 當batteries[i] >= m 則最多只能提供m的電力 多出來的b - m 用不到
            if (minutes >= n * m)                   // 因為時間已經到了 你沒辦法把電池換到其他電腦
                left = m + 1;
            else
                right = m;
        }
        return left - 1;
    }
};

/*

*/
