/*
 *  __自己的解法 但是TC超爛 不過還是AC__
 *
 *  1. 先把mat根據value從大到小排序 因為我要從大開始看
 *  2. 每個mat[y][x], 同時檢查相同row和column裡面 找出mat[y][x] < value更新 steps
 *  3. 把mat[y][x]存到對應的row和column 但是不同值最多只存兩個
 *
 */

class Solution {
public:
    int maxIncreasingCells(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> vec, steps(m, vector<int>(n));
        for(int y = 0; y < m; ++y) 
            for(int x = 0; x < n; ++x)
                vec.push_back({y, x});
        sort(begin(vec), end(vec), [&](auto& a, auto& b){ 
            return mat[a[0]][a[1]] > mat[b[0]][b[1]];
        });
        int ans{};
        unordered_map<int, deque<pair<int, int>>> my, mx;
        for(auto& v : vec) { // O(K)
            int& y = v[0], x = v[1];
            int steps{};
            for(auto& ref : my[y])
                if(ref.first > mat[y][x])
                    steps = max(steps, ref.second + 1);
            for(auto& ref : mx[x])
                if(ref.first > mat[y][x])
                    steps = max(steps, ref.second + 1);
            ans = max(ans, steps);
            if(!my[y].empty() && my[y].back().first == mat[y][x]) 
                my[y].back().second = max(my[y].back().second, steps);
            else
                my[y].push_back({mat[y][x], steps});
            if(my[y].size() > 2) my[y].pop_front();

            if(!mx[x].empty() && mx[x].back().first == mat[y][x]) 
                mx[x].back().second = max(mx[x].back().second, steps);
            else
                mx[x].push_back({mat[y][x], steps});
            if(mx[x].size() > 2) mx[x].pop_front();
        }
        return ans + 1;
    }
};
