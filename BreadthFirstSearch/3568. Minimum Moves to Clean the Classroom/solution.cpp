/*
 *      自己寫還是有些問題 所以參考gemini的解答
 *
 *
 */

class Solution {
    vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        int starty{}, startx{}, count{};
        for(int y = 0; y < m; ++y) for(int x = 0; x < n; ++x) {     // 先掃描全部的classroom找出'S' 和 'L' 的數目
            char cur = classroom[y][x];
            if(cur == 'S') {
                starty = y;
                startx = x;
            } else if(cur == 'L') {
                classroom[y][x] = '0' + count;                      // 把 'L' 轉成 offset大小 因為我們使用bit來記錄目前有哪些litter
                count++;
            }
        }
        if(count == 0) return 0;                                    // 沒有litter直接退出

        int total_li = 1 << count;
        int energy_cap = energy + 1;
        // 使用 1 維平鋪陣列取代 4 維 vector，大幅提升快取命中率並消除配置開銷
        // 索引公式: (((y * n + x) * energy_cap) + eng) * total_li + li
        auto get_idx = [&](int y, int x, int eng, int li) {                         // __important__ 本來是使用[y][x][eng][li] = step 但是效能不太好 所以改成一維
            return (((y * n + x) * energy_cap) + eng) * total_li + li;
        };

        vector<int> visited(m * n * energy_cap * total_li, INT_MAX);                // 紀錄[y][x][eng][li]的情況下最小step

        // 將 priority_queue 改為標準 queue (因為步數單調遞增，BFS 即可保證最優解)
        queue<tuple<int, int, int, int>> q; // y, x, li, eng

        int init_li = 0;
        q.push({starty, startx, init_li, energy});
        visited[get_idx(starty, startx, energy, init_li)] = 0;

        while(!q.empty()) {
            auto [y, x, li, eng] = q.front(); q.pop();
            int step = visited[get_idx(y, x, eng, li)];
            char cur = classroom[y][x];
            int n_eng = eng;
            int n_li = li;

            if(cur == 'R') {
                n_eng = energy;
            } else if(cur >= '0' && cur <= '9') {
                n_li |= (1 << (cur - '0'));
            }
            if(__builtin_popcount(n_li) == count) return step;

            // 能量耗盡且不在 R 區，無法繼續移動
            if(n_eng == 0) continue;

            for(auto& d : dirs) {                                                                   // 這邊只處理是否往下一個前進 不處理'R'和'L'的狀況 把她留給上半部
                int ny = y + d[0], nx = x + d[1];
                if(ny < 0 || nx < 0 || ny >= m || nx >= n || classroom[ny][nx] == 'X') continue;
                int next_eng = n_eng - 1;
                int next_idx = get_idx(ny, nx, next_eng, n_li);
                if(step + 1 < visited[next_idx]) {
                    visited[next_idx] = step + 1;
                    q.push({ny, nx, n_li, next_eng});
                }
            }
        }
        return -1;
    }
};
