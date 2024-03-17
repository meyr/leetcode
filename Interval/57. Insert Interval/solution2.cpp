/*
 *  參考解答 : https://leetcode.com/problems/insert-interval/solutions/1327206/99-16-faster-proper-explaination-c-solution-o-n/
 *  
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int i = 0, sz = intervals.size();
        vector<vector<int>> ans;
        while(i < sz && intervals[i][1] < newInterval[0]) // intervals[i] 還在 newInterval前面
            ans.push_back(intervals[i++]);
        while(i < sz && newInterval[1] >= intervals[i][0]) { // 和newInterval有交集 合併到newInterval
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.push_back(newInterval);
        while(i < sz) ans.push_back(intervals[i++]); // 把剩下的推到ans
        return ans;
    }
};
