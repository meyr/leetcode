/*  因為每個bulb可以點亮的是一個range 所以使用ranges來儲存可以點亮的區間
 *  每遇到lights[i] > 0 就產生一個range並且檢查是否可以向前合併
 *  最後計算每個區間的空格有多少
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    int minLights(vector<int>& lights) {
        int sz = lights.size();
        vector<vector<int>> ranges; //include, include
        ranges.push_back({-1, -1});
        for(int i = 0; i < sz; ++i) {
            if(lights[i]) {
                while(!ranges.empty() && ranges.back()[0] >= i - lights[i]) ranges.pop_back();
                if(!ranges.empty() && ranges.back()[1] >= i - lights[i]) ranges.back()[1] = max(ranges.back()[1], min(sz - 1, i + lights[i]));
                else ranges.push_back({max(0, i - lights[i]), min(sz - 1, i + lights[i])});
            }
        }

        ranges.push_back({sz, sz});

        int ans{};
        for(int i = 1; i < ranges.size(); ++i) {
            int space = ranges[i][0] - ranges[i - 1][1] - 1;
            if(space > 0) ans += (space + 2) / 3;
        }
        return ans;
    }
};
