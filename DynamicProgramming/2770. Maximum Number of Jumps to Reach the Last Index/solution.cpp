/*  一開始嘗試使用bottom up recursive dp來解 但是寫不太出來
 *  後來意識到應該可以用shortest problem來解 只是這次是重視最大值
 *  雖然可以AC但是time complexity不太好
 *
 *  time  : O(N^2logN)
 *  space : O(N)
 */
class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int sz = nums.size();
        vector<int> dist(sz, -1);
        dist[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});
        while(!pq.empty()) {
            auto [d, cur] = pq.top(); pq.pop();
            for(int nxt = cur + 1; nxt < sz; ++nxt) {
                if(abs(nums[cur] - nums[nxt]) <= target && d + 1 > dist[nxt]) {
                    dist[nxt] = d + 1;
                    pq.push({dist[nxt], nxt});
                }
            }
        }
        return dist.back();
    }
};
/*  後來使用top down tabulation dp solution
 *  time  : O(N^2) <-- 因為nums.length == n <= 1000
 *  space : O(N)
 */
class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int sz = nums.size();
        vector<int> dp(sz, -1);
        dp[0] = 0;
        for(int i = 0; i < sz; ++i) {
            if(dp[i] == -1) continue;
            for(int j = i + 1; j < sz; ++j) {
                if(abs(nums[i] - nums[j]) <= target && dp[i] + 1 > dp[j]) {
                    dp[j] = dp[i] + 1;
                }
            }
        }
        return dp.back();
    }
}; 
