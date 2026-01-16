/*
 * 切割一個會產生 width = 2的矩形, 如果連續兩個數字移除會產生 width = 3的矩形
 * 所以找出連續數字最多的地方 就可已得到最大的正方形
 *
 *  time  : O(logN + logM + N + M)
 *  space : O(logN + logM)
 */
class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        sort(begin(hBars), end(hBars));
        sort(begin(vBars), end(vBars));
        int hmax = hBars.empty() ? 1 : 2;
        for(int i = 1, cur = 2; i < hBars.size(); ++i) {
            if(hBars[i] == hBars[i - 1] + 1) cur += 1;
            else cur = 2;
            hmax = max(hmax, cur);
        }
        int vmax = vBars.empty() ? 1 : 2;
        for(int i = 1, cur = 2; i < vBars.size(); ++i) {
            if(vBars[i] == vBars[i - 1] + 1) cur += 1;
            else cur = 2;
            vmax = max(vmax, cur);
        }
        return pow(min(hmax, vmax), 2);
    }
};
