/*
 *  rhombus sum的定義是菱形邊長經過的grid才需要加起來 不是邊長包起來的grid的總和
 *  我一開始會錯誤 所以寫出來的解答是錯的
 *
 *  以一個點(y, x)為中心 可以圈出來的菱形如下
 *  有兩個邊是(+k, +k), 兩個邊是(-k, +k)
 *
 *                     (y - b, x)
 *           /                      \
 *          / (-k, +k)               \(+k, +k)
 *(y, x - b)              (y, x)        (y, x + b)
 *           \
 *            \                     / (-k, +k)
 *             \(+k, +k)           /
 *                      (y + b, x)
 *
 */

class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        auto check = [=](int y, int x, int b) -> bool {
            if(y - b < 0 || x - b < 0 || y + b >= m || x + b >= n) return false;
            else return true;
        };

        set<int> st;
        for(int y = 0; y < m; ++y) for(int x = 0; x < n; ++x) {
            st.insert(grid[y][x]);
            for(int b = 1; check(y, x, b); ++b) {
                int sum = grid[y - b][x] + grid[y + b][x] + grid[y][x - b] + grid[y][x + b];
                for(int k = 1; k < b; ++k)
                    sum += grid[y + k][x - b + k] +
                        grid[y - b + k][x + k] +
                        grid[y - k][x - b + k] +
                        grid[y + b - k][x + k];
                //cout << y << ", " << x << ", " << b << " : " << sum << endl;
                st.insert(sum);
            }
        }

        vector<int> rtn;
        for(auto it = st.rbegin(); it != st.rend() && rtn.size() < 3; ++it)
            rtn.push_back(*it);
        return rtn;
    }
};
