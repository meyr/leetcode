/*  第一個方法統計看過的index
 *
 *  time  : O(N^2) --> TLE 因為N=10^5必須是NlogN
 *  space : O(N)
 */
class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int sz = nums.size();
        vector<long long> rtn(sz);
        unordered_map<int, vector<int>> um;
        for(int i = 0; i < sz; ++i) {
            for(auto& prev : um[nums[i]])
                rtn[i] += i - prev;
            um[nums[i]].push_back(i);
        }
        um.clear();
        for(int i = sz - 1; i >= 0; --i) {
            for(auto& prev : um[nums[i]])
                rtn[i] += prev - i;
            um[nums[i]].push_back(i);
        }
        return rtn;
    }
};
/*
 * 考慮 index = n, prev = {p1, p2, p3}
 *      rtn[n] = n - p1 + n - p2 + n - p3
 *             = 3*n - (p1 + p2 + p3)      --> 所以使用pair<long long, int> 紀錄sum和count
 *
 * time  : O(N)
 * space : O(N)
 */
class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int sz = nums.size();
        vector<long long> rtn(sz);
        unordered_map<int, pair<long long, int>> um;
        for(int i = 0; i < sz; ++i) {
            if(um.count(nums[i])) {
                auto [total, count] = um[nums[i]];
                rtn[i] += 1LL * count * i - total;
            }
            um[nums[i]].first += i;
            um[nums[i]].second += 1;
        }
        um.clear();
        for(int i = sz - 1; i >= 0; --i) {
            if(um.count(nums[i])) {
                auto [total, count] = um[nums[i]];
                rtn[i] += total - 1LL * count * i;
            }
            um[nums[i]].first += i;
            um[nums[i]].second += 1;
        }
        return rtn;
    }
};
