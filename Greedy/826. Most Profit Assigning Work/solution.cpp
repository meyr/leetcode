/*
 *  Greedy point : 找出difficulty <= worker[i] 最大的profit 因為這樣才可以取得最大profit sum
 *
 *  1. 先把difficulty和profit combine成一個vector<vector<int>> dp
 *  2. 對 dp 依照difficulty排序
 *  3. 找出小於等於此difficulty的最大profit
 *  4. 使用binary search 針對每個worker找出對應的index
 *
 *
 *  time  : O(N + NlogN + N + MlogN) = O(NlogN + MlogN)
 *  space : O(N + longN) = O(N)
 */
class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        vector<vector<int>> dp;
        for(int i = 0; i < difficulty.size(); ++i) // O(N)
            dp.push_back({difficulty[i], profit[i]});
        sort(begin(dp), end(dp)); // O(NlogN)
        for(int i = 1; i < dp.size(); ++i) // O(N)
            dp[i][1] = max(dp[i - 1][1], dp[i][1]);
        int ans{};
        for(auto& w : worker) { // O(MlogN)
            int left = 0, right = dp.size();
            while(left < right) {
                int mid = left + (right - left) / 2;
                if(dp[mid][0] > w) right = mid;
                else left = mid + 1;
            }
            if(left > 0) 
                ans += dp[left - 1][1];
        }
        return ans;
    }
};

/*
    [2,   4,  6,  8, 10]
    [10, 20, 30, 40, 50]


*/
