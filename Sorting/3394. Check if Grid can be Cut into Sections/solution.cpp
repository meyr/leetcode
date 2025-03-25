/*  根據 x-axis和y-axis來計算可以切割的數目
 *
 *  time  : O(NlogN + N + NlogN + N) = O(NlogN)
 *  space : O(logN) for sorting
 *
 */
class Solution {
    enum pos{
        xs, ys, xe, ye
    };
public:
    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        // sort by y-axis
        sort(begin(rectangles), end(rectangles), [](auto& a, auto& b){
            if(a[ys] < b[ys]) return true;
            else if(a[ys] == b[ys]) return a[ye] > b[ye];
            return false;
        });
        int cnt{-1};
        for(int i = 0, prev = -1; i < rectangles.size(); ++i) {
            if(rectangles[i][ys] >= prev)
                cnt++;
            prev = max(prev, rectangles[i][ye]);
        }
        if(cnt >= 2) return true;
        sort(begin(rectangles), end(rectangles), [](auto& a, auto& b){
            if(a[xs] < b[xs]) return true;
            else if(a[xs] == b[xs]) return a[xe] > b[xe];
            return false;
        });
        cnt = -1;
        for(int i = 0, prev = -1; i < rectangles.size(); ++i) {
            if(rectangles[i][xs] >= prev)
                cnt++;
            prev = max(prev, rectangles[i][xe]);
                
        }
        return cnt >= 2;       
    }
};
/*
    [0, 2][1, 3][2, 3][3, 4][3, 4]


*/
