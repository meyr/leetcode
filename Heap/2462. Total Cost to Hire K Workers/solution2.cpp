/*
 *  參考解答
 *  因為左右兩邊可以分別使用兩個minhq
 *  可以減少很多比對和錯誤
 *
 */

class Solution {
    template<typename T>
    using minhp = priority_queue<T, vector<T>, greater<>>;
public:
    long long totalCost(vector<int>& costs, int k, int candidates) {
        int sz = costs.size();
        long long ans{};
        int left = 0, right = sz - 1;
        minhp<int> pq1, pq2;
        while(left < min(candidates, sz)) pq1.push(costs[left++]);
        while(right >= max(left, sz - candidates)) pq2.push(costs[right--]);
        while(k--) {
            int a = pq1.empty() ? INT_MAX : pq1.top();
	    int b = pq2.empty() ? INT_MAX : pq2.top();
            if(a <= b) {
                ans += a;
                pq1.pop();
                if(left <= right) pq1.push(costs[left++]);
            } else {
                ans += b;
                pq2.pop();
                if(left <= right) pq2.push(costs[right--]);
            }
        }
        return ans;
    }
};

