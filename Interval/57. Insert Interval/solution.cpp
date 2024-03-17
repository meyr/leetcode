/*
 *    沒利用到sorted intervals特性 不是很好的解法
 *
 *    time  : O(NlogN + N) = O(NlogN)
 *    space : O(N) 
 */

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.push_back(newInterval);
        sort(begin(intervals), end(intervals)); // O(NlogN)
        vector<vector<int>> ans;
        ans.push_back(intervals.front());
        for(int i = 1; i < intervals.size(); ++i) { //O(N)
            if(min(intervals[i][1], ans.back()[1]) >= 
               max(intervals[i][0], ans.back()[0])) {
                    ans.back()[0] = min(intervals[i][0], ans.back()[0]);
                    ans.back()[1] = max(intervals[i][1], ans.back()[1]); 
            } else
                ans.push_back(intervals[i]);
        }
        return ans;
    }
};
