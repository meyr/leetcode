/*
 *
 *  time  : O(NK)
 *  space : O(NK)
 */
class Solution {
    int n, k;
    int helper(vector<vector<int>>& stay, vector<vector<int>>& travel, int cur, int day) {
        if(day == k) return 0;
        if(~mem[cur][day]) return mem[cur][day];
        int ans{};
        for(int nxt = 0; nxt < n; ++nxt) {
            int score = cur == nxt ? stay[day][cur] : travel[cur][nxt];
            ans = max(ans, helper(stay, travel, nxt, day + 1) + score);
        }
        return mem[cur][day] = ans;
    }
    vector<vector<int>> mem;
public:
    int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {
        int ans{};
        this->n = n;
        this->k = k;
        mem.resize(n, vector<int>(k, -1));
        for(int i = 0; i < n; ++i)
            ans = max(ans, helper(stayScore, travelScore, i, 0));
        return ans;
    }
};
