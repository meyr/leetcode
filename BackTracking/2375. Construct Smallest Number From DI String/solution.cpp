/* 一開始使用Backtracking找所有的可能 只要一找到就返回
 * 因為要 lexicographically smallest possible string 所以每次都從最小的可能開始找 (1)(2)
 *
 */
class Solution {
    bool helper(string& pattern, vector<int>& used, int idx, string& ans) {
        if(idx == pattern.size()) return true;
        int prev = ans.back() - '0';
        if(pattern[idx] == 'I') {   // increase
            for(int i = prev + 1; i <= 9; ++i) {    // (1)
                if(!used[i]) {
                    ans.push_back(i + '0');
                    used[i] = 1;
                    if(helper(pattern, used, idx + 1, ans)) return true;
                    used[i] = 0;
                    ans.pop_back();
                }
            }
        } else {                    // decrease
            for(int i = 1; i < prev; ++i) {         // (2)
                if(!used[i]) {
                    ans.push_back(i + '0');
                    used[i] = 1;
                    if(helper(pattern, used, idx + 1, ans)) return true;
                    used[i] = 0;
                    ans.pop_back();
                }
            }
        }
        return false;
    }
public:
    string smallestNumber(string pattern) {
        vector<int> used(10);
        string ans{};
        for(int i = 1; i <= 9; ++i) {
            ans.push_back(i + '0');
            used[i] = 1;
            if(helper(pattern, used, 0, ans))
                return ans;
            used[i] = 0;
            ans.pop_back();
        }
        return "";
    }
};
/*  想法一樣 改用數字 最後結果再轉成string
 *
 */
class Solution {
    int helper(string& p, int cur, int idx, bitset<10>& used) {
        if(idx == p.size()) return cur;
        int prev = cur % 10;
        for(int i = 1; i <= 9; ++i) {
            if(!used.test(i) && (p[idx] == 'I' ? i > prev : i < prev)) {
                used.set(i);
                if(int ans = helper(p, cur * 10 + i, idx + 1, used)) return ans;
                used.reset(i);
            } 
        }
        return 0;
    }
public:
    string smallestNumber(string pattern) {
        for(int n = 1; n <= 9; ++n) {
            bitset<10> used;
            used.set(n);
            if(int ans = helper(pattern, n, 0, used))
                return to_string(ans);
        }
        return "";
    }
};
/*  參考解答:https://leetcode.com/problems/construct-smallest-number-from-di-string/solutions/2422290/dfs-vs-greedy-by-votrubac-mx84/
 *  想法類似
 */
class Solution {
    int dfs(string& p, int i, int n, int mask) {
        if (i > p.size())
            return n;
        int res = INT_MAX, last = n % 10, increment = i == 0 || p[i - 1] == 'I';
        for (int d = 1; res == INT_MAX && d <= 9; ++d)
            if ((mask & (1 << d)) == 0 && last < d == increment)
                res = dfs(p, i + 1, n * 10 + d, mask + (1 << d));
        return res;
    }
public:
    string smallestNumber(string pattern) {
        return to_string(dfs(pattern, 0, 0, 0));
    }
};
/*
 *  參考解答:https://leetcode.com/problems/construct-smallest-number-from-di-string/solutions/2422290/dfs-vs-greedy-by-votrubac-mx84/
 *
 *  Then, I realized that we can start with the smallest possible answer - "123456789" (all numbers increasing).
 *
 *  If we have decreasing intervals, we reverse the string for those intervals.
 *
 */
class Solution {
public:
    string smallestNumber(string p) {
        string res;
        for (int i = 0, j = 0; i <= p.size(); ++i) {
            res.push_back('1' + i);
            if (i == p.size() || p[i] == 'I') {     // 遇到I或是尾端就翻轉前面的string
                reverse(begin(res) + j, end(res));
                j = i + 1;                          // p[i] = 'D' j就不會前進 --> 紀錄第一個D的起點
            }
        }
        return res;
    }
};
/*
I:1
I:12
I:123
D:1234
I:12354 (reverse)
D:123546
D:1235467
D:12354678
*/
