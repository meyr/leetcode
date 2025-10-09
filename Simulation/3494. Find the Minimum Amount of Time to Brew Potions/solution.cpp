/*  參考: https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/solutions/7260348/minimum-amount-of-time-brew-potions-most-3vvw/
 *
 *
 *
 *  time  : O(MN)
 *  space : O(N)
 */

class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size(), m = mana.size();
        vector<long long> done(n + 1, 0);
        
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                done[i + 1] = max(done[i + 1], done[i]) + 1LL * mana[j] * skill[i];
            }
            for (int i = n - 1; i > 0; --i) {
                done[i] = done[i + 1] - 1LL * mana[j] * skill[i];
            }
        }
        
        return done[n];
    }
};
