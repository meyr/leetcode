/*
 *  根據第一個想法 如果對worker排序 則不需要binary search 只需要用two pointers
 *
 *  time  : O(N + NlogN + MlogM + N + M + N) = O(NlogN + MlogM)
 *  space : O(N + logN + logM) = O(N)
 */

class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        vector<vector<int>> dp;
        for(int i = 0; i < difficulty.size(); ++i) // O(N)
            dp.push_back({difficulty[i], profit[i]});
        sort(begin(dp), end(dp)); // O(NlogN)
        sort(begin(worker), end(worker)); // O(MlogM)
        for(int i = 1; i < dp.size(); ++i) // O(N)
            dp[i][1] = max(dp[i - 1][1], dp[i][1]);
        int ans{};
        int i = 0, j = 0;
        while(j < worker.size()) { // O(M + N)
            while(i < dp.size() && dp[i][0] <= worker[j]) ++i;    
            if(i > 0) ans += dp[i - 1][1];
            j++;
        }
        return ans;
    }
};

// 2024/06/18
// 和上面的概念相同
class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        vector<vector<int>> dp; // dicciculty, profit
        for(int i = 0; i < difficulty.size(); ++i) dp.push_back({difficulty[i], profit[i]});
        sort(begin(dp), end(dp));
        sort(begin(worker), end(worker));
        int ans{}, maxprofit{};
        for(int i = 0, j = 0; i < worker.size(); ++i) { // O(M + N) 因為worker和dp都會只走過一次
            while(j < dp.size() && worker[i] >= dp[j][0])
                maxprofit = max(maxprofit, dp[j++][1]);
            ans += maxprofit;
        }
        return ans;
    }
    // time : O(N + NlogN + MlogM + M + N) = O(NlogN + MlogM)
    // space : O(N + logN + logM) = O(N)
};
