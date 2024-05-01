/*
 *    按照題意使用minhp來解題
 *
 *
 */

class Solution {
    template<typename T>
    using minhp = priority_queue<T, vector<T>, greater<>>;
public:
    long long totalCost(vector<int>& costs, int k, int candidates) {
        int sz = costs.size();
        int left = 0, right = sz - 1;
        minhp<pair<int, int>> pq;
        for(; left < min(sz, candidates); ++left) pq.push({costs[left], left});
        for(; right >= sz - candidates && left <= right; right--) pq.push({costs[right], right});
        long long ans{};
        while(k--) {
            auto [c, idx] = pq.top(); pq.pop();
            ans += c;
            if(idx < left && left <= right) pq.push({costs[left], left++});
            if(idx > right && left <= right) pq.push({costs[right], right--});
        }
        return ans;
    }
};
/*
    0, 1, 2, 3, 4   sz = 5, candidates = 2
            -----
    ----
*/
