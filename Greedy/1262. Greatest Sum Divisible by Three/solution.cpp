/* Greedy point: 因為要取總和最大值，所以全部加起來就是最大值
 *               如果總和不是3的倍數，那就減掉最少的數讓他可以符合
 *
 *  time  : O(NlogN + N) = O(NlogN)
 *  space : O(logN + N) = O(N)
 */

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        sort(begin(nums), end(nums));
        int ans{};
        unordered_map<int, vector<int>> um;
        for(const auto& n : nums) {
            ans += n;
            int mod = n % 3;
            if(mod != 0)
                um[mod].push_back(n);
        }
        if(ans % 3 == 0) return ans;
        else if(ans % 3 == 1) {
            int target = ans;
            if(!um[1].empty()) target = min(target, um[1][0]);
            if(um[2].size() >= 2) target = min(target, um[2][0] + um[2][1]);
            return ans - target;
        } else {
            int target = ans;
            if(!um[2].empty()) target = min(target, um[2][0]);
            if(um[1].size() >= 2) target = min(target, um[1][0] + um[1][1]);
            return ans - target;
        }
    }
};
