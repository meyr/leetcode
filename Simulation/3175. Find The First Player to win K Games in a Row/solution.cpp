/*
 *  依照題意模擬遊戲過程 
 *  special case k >= sz 只需要找出最大值player
 *
 *  time  : O(N + N) = O(N)
 *  sapce : O(N)
 */
class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k) {
        int sz = skills.size();
        if(k >= sz) return max_element(begin(skills), end(skills)) - begin(skills);
        queue<int> q;
        vector<int> cnt(sz);
        for(int i = 1; i < sz; ++i) q.push(i);
        int winner = 0;
        while(1) {
            int challenger = q.front(); q.pop();
            if(skills[winner] < skills[challenger])
                swap(winner, challenger);
            if(++cnt[winner] == k)
                return winner;
            q.push(challenger);
        }
        return -1;
    }
};
/*  參考解答 : https://leetcode.com/problems/find-the-first-player-to-win-k-games-in-a-row/solutions/5280219/java-c-python-one-pass-best-is-always-the-best/
 *
 *  因為後面來的challenger如果贏了 count會從0開始
 *  當每個player都輪過了 結果一定是最大的
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k) {
        int winner = 0, count = 0;
        for(int challenger = 1; challenger < skills.size(); ++challenger) {
            if(skills[challenger] > skills[winner]) {
                winner = challenger;
                count = 0;
            }
            if(++count == k) break;
        }
        return winner;
    }
};
