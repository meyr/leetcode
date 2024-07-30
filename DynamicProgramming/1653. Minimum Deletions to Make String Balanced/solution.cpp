/*
 * 參考: https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/solutions/935701/dp-solution-beats-100-with-explanation/
 *
 * 改成top-down recurisive + memorization會出現MLE
 *
 */

class Solution {
    int helper(string& s, int idx, int bcount) {
        if(~mem[idx][bcount]) return mem[idx][bcount];
        else if(s[idx] == 'b') return mem[idx][bcount] = helper(s, idx + 1, bcount + 1); // 不需要移除任何char
        else return mem[idx][bcount] = min(helper(s, idx + 1, bcount) + 1,  // 移除目前char
                                           helper(s, idx + 1, 0) + bcount); // 移除之前所有的b
    }
    vector<vector<int>> mem;
public:
    int minimumDeletions(string s) {
        int sz = s.size();
        mem.resize(sz + 1, vector<int>(sz + 1, -1));
        for(int i = 0; i <= sz; ++i)
            mem[sz][i] = 0;
        return helper(s, 0, 0);
    }
};

/*
 * 改成bottom-up tabulation 原本的解法 就可以AC
 */
class Solution {
public:
    int minimumDeletions(string s) {
        int sz = s.size();
        vector<int> dp(sz + 1);
        int bcount{};
        for(int i = 0; i < sz; ++i) {
            if(s[i] == 'a') 
                dp[i + 1] = min(dp[i] + 1, bcount); // remote this or remove all 'b' before
            else {
                dp[i + 1] = dp[i];
                bcount++;
            }
        }
        return dp.back();
    }
};
/*
 * 參考 : https://leetcode.cn/problems/minimum-deletions-to-make-string-balanced/solutions/2147032/shi-zi-fu-chuan-ping-heng-de-zui-shao-sh-l5lk/
 *
 * 只有三種可能
 * 1. "aa...aa"  都是a
 * 2. "bb...bb"  都是b
 * 3. "aaa..bbb" a都在b前面
 *               可以在原字符串相鄰的兩個字符之間劃一條間隔，刪除間隔左側所有的 “b” 和間隔右側所有的 “a” 即可達到。
 * 
 * time  : O(N)
 * space : O(1)
 */
class Solution {
public:
    int minimumDeletions(string s) {
        int cnta{}, cntb{};
        for(auto& c : s) cntb += c == 'b';
        int ans = cntb;
        for(int i = s.size() - 1; i >= 0; --i) {
            cnta += s[i] == 'a';
            cntb -= s[i] == 'b';
            ans = min(ans, cntb + cnta);
        }
        return ans;
    }
};
