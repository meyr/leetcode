/*  先找出每個char出現的最左邊和最右邊的idx
 *  再計算[left, right]中間出現的unique char 就是可以組成所有length-3 palindromic 
 *
 *  time  : O(N + 26*N) = O(N)
 *  space : O(26*2) = O(1) 
 */
class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int sz = s.size();
        vector<vector<int>> idx(26, vector<int>{sz, -1});
        for(int i = 0, j = s.size() - 1; i < s.size(); ++i, --j) {
            char ci = s[i] - 'a', cj = s[j] - 'a';
            idx[ci][0] = min(idx[ci][0], i);
            idx[cj][1] = max(idx[cj][1], j);
        }
        int ans{};
        for(char c = 0; c < 26; ++c) {
            int left = idx[c][0], right = idx[c][1];
            if(right - left >= 2)
                ans += unordered_set<char>(begin(s) + left + 1, begin(s) + right).size();
        }
        return ans;
    }
};
