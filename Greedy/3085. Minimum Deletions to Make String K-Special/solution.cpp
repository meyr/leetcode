/*  參考: https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/solutions/4886196/explained-using-simple-freq-check-by-kre-kh7f/
 *  
 *  time  : O(N)  因為sort和兩個for loop不會因為word變長就變多，都是K=26, O(KlogK + K^2)
 *  space : O(1)  不會因為word變長就變多，都是26個
 */
class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> freq(26);
        for(auto& c : word) freq[c - 'a']++;
        sort(begin(freq), end(freq));
        int del{}, ans = word.size();
        for(int i = 0; i < freq.size(); ++i) {
            int res = del;
            for(int j = freq.size() - 1; j > i; --j) {
                if(freq[j] - freq[i] <= k) break;
                res += freq[j] - freq[i] - k; // __important__ 
                                              // 不刪除freq[i]的情況下, 刪除freq[j]
                                              // 能滿足條件式
                                              // freq[j] - x = freq[i] + k
                                              // x = freq[j] - freq[i] - k
            }
            ans = min(ans, res);
            del += freq[i]; // 往前進，全部都刪除
        }
        return ans;
    }
};
