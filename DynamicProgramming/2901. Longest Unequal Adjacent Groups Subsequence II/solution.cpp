/*  使用vector<int> dp來記錄每個index最長的subsequence
 *  使用vector<int> prev來記錄前一個index是多少
 *
 *  time  : O(N^2*M), N : size of words, M : size of words[i]
 *  space : O(N)
 */
class Solution {
    bool diff(string& str1, string& str2) {
        if(str1.size() != str2.size()) return false;
        int cnt{};
        for(int i = 0; i < str1.size(); ++i) {
            cnt += str1[i] != str2[i];
            if(cnt > 1) break;
        }
        return cnt == 1;
    }
public:
    vector<string> getWordsInLongestSubsequence(vector<string>& words, vector<int>& groups) {
        int sz = words.size(), maxidx{-1}, maxlen{0};
        vector<int> dp(sz, 1), prev(sz);
        iota(begin(prev), end(prev), 0);
        for(int i = 0; i < sz; ++i) {
            for(int j = i - 1; j >= 0; --j) {
                if(groups[i] != groups[j] && diff(words[i], words[j])) {
                    if(dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        prev[i] = j;
                    }
                }
            }
            if(dp[i] > maxlen) {
                maxlen = dp[i];
                maxidx = i;
            }
        }
        vector<string> ans(maxlen);
        for(int i = maxlen - 1; i >= 0; --i) {
            ans[i] = words[maxidx];
            maxidx = prev[maxidx];
        }

        return ans;
    }
};
