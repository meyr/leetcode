/*
 *  score的定義為 values[i] + values[j] + i - j
 *
 *  可以寫為values[i] + i + valuses[j] - j
 *
 *  因為是找出最大score 所以每次找出最大的values[i] + i 就可以得到最大的score
 *
 *  time  : O(N)
 *  space : O(1)
 *
 */
class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int ans{}, maxv = values[0];
        for(int j = 1; j < values.size(); ++j) {
            ans = max(ans, maxv + values[j] - j);
            maxv = max(maxv, values[j] + j); 
        }
        return ans;
    }
};
