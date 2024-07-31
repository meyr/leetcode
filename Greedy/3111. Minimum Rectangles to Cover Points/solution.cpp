/*
 * 一開始以為是DP問題 結果是Greedy問題
 * Greedy point: 每個regtangular盡量包含最多的points
 *
 * time  : O(NlogN + N) = O(NlogN)
 * space : O(logN)
 */
class Solution {
public:
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w) {
        sort(begin(points), end(points));
        int ans{};
        for(int cur = 0, prev = 0; cur < points.size();) {
            while(cur < points.size() && points[cur][0] - points[prev][0] <= w) cur++;
            ans++;
            prev = cur;
        }
        return ans;
    }
};

/*
 * 參考官方解答 : https://leetcode.cn/problems/minimum-rectangles-to-cover-points/solutions/2857796/fu-gai-suo-you-dian-de-zui-shao-ju-xing-xduq9/
 * 
 * 想法類似 改成追蹤regtangular最遠到哪裡 bound
 * 
 * time  : O(NlogN)
 * space : O(logN)
 */

class Solution {
public:
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w) {
        sort(points.begin(), points.end());
        int res = 0;
        int bound = -1;
        for (auto &p : points) {
            if (p[0] > bound) {
                bound = p[0] + w;
                res++;
            }
        }
        return res;
    }
};
