/*  每個數值都有bounds[i] 從original[i+1] - original[i] = d 推到bounds[i + 1]
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    int countArrays(vector<int>& original, vector<vector<int>>& bounds) {
        for(int i = 0; i < original.size() - 1; ++i) {
            int d = original[i + 1] - original[i];
            bounds[i + 1][0] = max(bounds[i + 1][0], bounds[i][0] + d);
            bounds[i + 1][1] = min(bounds[i + 1][1], bounds[i][1] + d);
            if(bounds[i + 1][0] > bounds[i + 1][1]) return 0;
        }
        return bounds.back()[1] - bounds.back()[0] + 1;
    }
};
