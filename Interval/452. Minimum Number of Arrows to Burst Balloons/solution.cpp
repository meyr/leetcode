/*
 *  先對Intervals排序 然後計算重複的個數
 *
 *  time  : O(NlogN + N) = O(NlogN)
 *  space : O(logN) 
 */

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(begin(points), end(points), [](auto& a, auto& b){
            if(a[1] < b[1]) return true;
            else if(a[1] == b[1]) return a[0] < b[0];
            else return false;
        });
        int ans{1};
        for(int i = 1, prev = 0; i < points.size(); ++i) {
            if(points[i][0] > points[prev][1]) {
                ans++;
                prev = i;
            }
        }
        return ans;
    }
};
