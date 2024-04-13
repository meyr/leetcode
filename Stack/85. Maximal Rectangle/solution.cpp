/*
 *  1. 先統計horizontal的連續'1'的個數
 *  2. 從目前的位置往上看，目前的width(hmin)為多少，只需紀錄最小值
 *
 */
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int ans{}, m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> h(m, vector<int>(n));
        for(int y = 0; y < m; ++y) { // method 1
            for(int x = 0; x < n; ++x) { // method 1
                if(x == 0) h[y][x] = matrix[y][x] - '0';
                else h[y][x] = matrix[y][x] == '0' ? 0 : h[y][x - 1] + 1;
                int hmin = 201;
                for(int k = y; k >= 0 && hmin > 0; --k) { // method 2
                    hmin = min(hmin, h[k][x]);
                    ans = max(ans, hmin * (y - k + 1));
                }
            }
        }
        // time  : O(MNM) = O(NM^2)
        // space : O(NM)
        return ans;
    }
};
