/*  一開始以為是DP的問題 但是馬上意識到如果要做memorization 要存相當大的空間
 *  後來想到是Greedy問題 因為我們要最長的subsequence所以不斷取0 並且有策略的取1不要超過 k
 *
 *  Greedy point : 從後面開始取 遇到'1'就檢查是否會超過k 不會就取 遇到'0'都取
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    int longestSubsequence(string s, int k) {
        int ans{};
        long long val{};
        for(int i = s.size() - 1; i >= 0; --i) {
            if(s[i] == '1') {
                if(ans < 33 && (val | (1L << ans)) <= k) {
                    val |= 1 << ans;
                    ans++;
                }
            } else
                ans++;
        }
        return ans;
    }
};
