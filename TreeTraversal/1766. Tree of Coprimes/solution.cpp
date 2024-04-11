/*
 *   參考 : https://leetcode.com/problems/tree-of-coprimes/solutions/1074770/c-save-the-cops/
 *
 *   因為數值只有1 <= nums[i] <= 50，所以建立co-primes table成本很小
 *   從co-primes來找ancestor會比較有效率
 */
class Solution {
    unordered_map<int, vector<int>> cops;
    unordered_map<int, vector<pair<int, int>>> ancestors; // value, <level, node>
    unordered_map<int, vector<int>> adj;
    vector<int> res;
    void helper(vector<int>& nums, int cur, int prev, int level) {
        int max_level = -1; // 目前可以找到最近的ancestor的level
        for(auto& cop : cops[nums[cur]]) { // 先找出co-prime的數值
            auto& v = ancestors[cop]; // 根據co-prime的數值，找出對應的ancestors node
            if(!v.empty() && v.back().first > max_level) { // 只需比較最後面的v.back() 是否比較靠近cur
                max_level = v.back().first;
                res[cur] = v.back().second;
            }
        }
        ancestors[nums[cur]].push_back(make_pair(level, cur));
        for(auto& nxt : adj[cur]) {
            if(nxt == prev) continue;
            helper(nums, nxt, cur, level + 1);
        }
        ancestors[nums[cur]].pop_back();
    }
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        unordered_set<int> s(begin(nums), end(nums));
        for(auto& n1 : s) {
            for(auto& n2 : s) {
                if(__gcd(n1, n2) == 1)
                    cops[n1].push_back(n2);
            }
        }
        int sz = nums.size();
        res.resize(sz, -1);
        for(auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        helper(nums, 0, 0, 0);
        return res;
    }
};
