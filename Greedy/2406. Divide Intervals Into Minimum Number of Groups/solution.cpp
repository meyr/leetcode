/*
 *  Greedy point : 優先使用先結束的intervals --> 使用minheap
 *                 很多這種類似的作法 
 *
 *  time  : O(NlogN + NlogN) = O(NlogN)
 *  space : O(logN + N) = O(N)
 */
class Solution {
template<typename T>
using minheap = priority_queue<T, vector<T>, greater<>>;
public:
    int minGroups(vector<vector<int>>& intervals) {
        sort(begin(intervals), end(intervals));
        minheap<int> pq;
        int ans{};
        for(int i = 0; i < intervals.size(); ++i) {
            if(!pq.empty() && pq.top() < intervals[i][0])
                pq.pop();
            pq.push(intervals[i][1]);
            ans = max(ans, (int)pq.size());
        }
        return ans;
    }
};
