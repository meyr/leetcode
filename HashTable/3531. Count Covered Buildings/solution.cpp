/*  
 *     0     1     2     3     4      no
 *  [[1,2],[2,2],[3,2],[2,1],[2,3]]
 *
 *     x1 : 0           1
 *     x2 : 3, 1, 4     3
 *     x3 : 2           1
 *
 *     y1 : 3           1
 *     y2 : 0 1 2       3
 *     y3 : 4           1
 *
 *   分別針對axis-x和axis-y收集點數
 *   先針對axis-x來排序 中間點就是滿足axis-x的 buildings
 *   再針對axis-y來排序 中間點就是滿足axis-y的 buildings且也滿足axis-x就把ans+1
 *
 *   time  : O(N + NlogN + NlogN) = O(NlogN)
 *   space : O(N + N + logN + logN) = O(N)
 */
class Solution {
    enum position{
        x,
        y
    };
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        int sz = buildings.size();
        unordered_map<int, vector<int>> axis_x, axis_y;
        for(int i = 0; i < sz; ++i) {
            vector<int>& b = buildings[i];
            axis_x[b[x]].push_back(i);
            axis_y[b[y]].push_back(i);
        }
        unordered_set<int> us;
        for(auto& ref : axis_x) {
            vector<int>& vec = ref.second;
            if(vec.size() >= 3) {
                sort(begin(vec), end(vec), [&](auto& i, auto& j){
                    return buildings[i][y] < buildings[j][y];
                });
                for(int i = 1; i < vec.size() - 1; ++i)
                    us.insert(vec[i]);
            }
        }
        int ans{};
        for(auto& ref : axis_y) {
            vector<int>& vec = ref.second;
            if(vec.size() >= 3) {
                sort(begin(vec), end(vec), [&](auto& i, auto& j){
                    return buildings[i][x] < buildings[j][x];
                });
                for(int i = 1; i < vec.size() - 1; ++i)
                    ans += us.count(vec[i]);
            }
        }
        return ans;
    }
};
/*
 *  參考: https://leetcode.com/problems/count-covered-buildings/solutions/6690614/binary-search-map-explained-with-images-8ubh7/
 *
 *  使用pair<iterator, iterator> = xx.equal_range(key) 找出你給定的key第一個出現的iterator(也就是lower_bound)和大於key的iterator(也就是upper_bound)
 *  其中可以使用的container為set, multiset, map, multimap
 *
 */
class Solution {
    enum position{
        x,
        y
    };
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        unordered_map<int, set<int>> axis_x, axis_y;
        for(auto& b : buildings) {
            axis_x[b[x]].insert(b[y]);
            axis_y[b[y]].insert(b[x]);
        }
        int ans{};
        for(auto& b : buildings) {
            auto& set_x = axis_x[b[x]];
            auto& set_y = axis_y[b[y]];

            auto [left, right] = set_x.equal_range(b[y]);
            auto [down, up]    = set_y.equal_range(b[x]);
            bool not_leftmost  = left != set_x.begin();
            bool not_rightmost = right != set_x.end();
            bool not_bottom    = down != set_y.begin();
            bool not_top       = up   != set_y.end();

            ans += not_leftmost && not_rightmost && not_bottom && not_top;
        }
        return ans;
    }
};
/*   參考TC最佳解答
 *   決定每個row column的最大最小值
 *   只要在中間的都是答案
 *
 *   time  : O(N + N) = O(N)
 *   space : O(N + N + N + N) = O(N)
 *
 */
class Solution {
    enum position{
        x,
        y
    };
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        vector<int> maxUp(n + 1), maxRight(n + 1);
        vector<int> minDown(n + 1, n + 1), minLeft(n + 1, n + 1);
        for(const auto& b : buildings) {
            const int& x = b[0], y = b[1];
            maxUp[x]    = max(maxUp[x],    y);
            minDown[x]  = min(minDown[x],  y);
            maxRight[y] = max(maxRight[y], x);
            minLeft[y]  = min(minLeft[y], x);
        }
        int ans{};
        for(const auto& b : buildings) {
            const int& x = b[0], y = b[1];
            bool not_leftmost  = x > minLeft[y];
            bool not_rightmost = x < maxRight[y];
            bool not_bottom    = y > minDown[x];
            bool not_up        = y < maxUp[x];
            ans += not_leftmost && not_rightmost && not_bottom && not_up;
        }
        return ans;
    }
};
