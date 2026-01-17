/*
    for x-axis
    1               3
    -----------------
             -----------------------
             2                     4
             ---------   重疊的一個邊

    for y-axis
    1                3
    ------------------
            ------------------------
            2                       4
            ---------   重疊的另一個邊


            兩個邊取最小值就是可以塞入的Rectangle

   time  : O(N^2)
   space : O(1)
*/
class Solution {
    enum position{
        x,
        y
    };
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int ans{};
        int sz = bottomLeft.size();
        for(int i = 1; i < sz; ++i) {
            for(int j = 0; j < i; ++j) {
                int xs = max(bottomLeft[i][x], bottomLeft[j][x]);
                int xe = min(topRight[i][x], topRight[j][x]);
                if(xe <= xs) continue;
                int ys = max(bottomLeft[i][y], bottomLeft[j][y]);
                int ye = min(topRight[i][y], topRight[j][y]);
                if(ye <= ys) continue;
                ans = max(ans, min(xe - xs, ye - ys));                
            }
        }
        return (long long)ans * ans;
    }
};

