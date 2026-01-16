/*
 *
 *
 *
 */
class Solution {
    enum turns{
        mouseTurn,
        catTurn,
        turn_size
    };
    enum result{
        draw,
        mouseWin,
        catWin,
        result_size
    };
    enum position {
        hole,
        mouseStart,
        catStart
    };
public:
int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();
        // results[mouse][cat][turn]: 0-平手, 1-鼠贏, 2-貓贏
        // turn: 1 是鼠, 2 是貓
        int results[51][51][result_size] = {draw}; // 目前遊戲所有的狀態
        int degree[51][51][turn_size] = {0};     // 通到此處的可能性

        // 1. 初始化出度 (Degree)
        for (int m = 0; m < n; ++m) {
            for (int c = 0; c < n; ++c) {
                degree[m][c][mouseTurn] = graph[m].size(); // mouse每條路都可以走 
                degree[m][c][catTurn] = 0;                
                for (int next_c : graph[c]) // 貓不能進hole，所以每個都要檢查
                    degree[m][c][catTurn] += next_c != hole;
            }
        }

        // 2. 初始已知狀態 (鼠在0，或貓鼠同位置)
        // 佇列儲存: {mouse, cat, turn, result}
        queue<tuple<int, int, int, int>> q;

        for (int i = 1; i < n; ++i) { // 不管cat在什麼位置
            //只要老鼠在洞口 (0)，老鼠贏 (1)
            results[hole][i][mouseTurn] = mouseWin;
            results[hole][i][catTurn]   = mouseWin;
            q.push({hole, i, mouseTurn, mouseWin});
            q.push({hole, i, catTurn, mouseWin});

            // 只要貓鼠同位，貓贏 (2)
            results[i][i][mouseTurn] = catWin;
            results[i][i][catTurn] = catWin;
            q.push({i, i, mouseTurn, catWin});
            q.push({i, i, catTurn, catWin});
        }

        // 3. 拓撲排序反向推導
        while (!q.empty()) {
            auto [m, c, t, res] = q.front();
            q.pop();

            // 如果已經推導到遊戲起點 (鼠在1, 貓在2, 鼠先手)
            if (m == mouseStart && c == catStart && t == mouseTurn) return res;

            // 找出上一個可能的狀態 (prev_m, prev_c, prev_t)
            int prev_t = t == mouseTurn ? catTurn : mouseTurn;// 1:mouseTurn --> 2 catTurn, 2 catTurn --> 1 : mouseTurn
            if (prev_t == mouseTurn) { // 上一步是鼠走，所以我們要找哪些節點可以走到目前的 m
                for (int prev_m : graph[m]) { // 可以走到m的所有情況prev_m
                    if (results[prev_m][c][mouseTurn] == draw) { // 因為預設狀態為draw 表示還不確定是cat win或是mouse win
                        // 如果這步能讓鼠贏
                        if (res == mouseWin) { // 如果目前是mouse win，且上一步換老鼠走，老鼠當然會選擇對自己最有利的，走到m
                            results[prev_m][c][mouseTurn] = mouseWin; // 把上一個狀態設定成老鼠贏
                            q.push({prev_m, c, mouseTurn, mouseWin}); // 把狀態放入queue繼續往前一個推  
                        } 
                        // 如果這步是鼠走，但目前結果是貓贏，則減少鼠的出度
                        // 因為往這邊走cat win所以老鼠就往其他地方走
                        // 如果degree == 0表示沒地方可以走了，那就是cat win
                        else if (--degree[prev_m][c][mouseTurn] == 0) {
                            results[prev_m][c][mouseTurn] = catWin;
                            q.push({prev_m, c, mouseTurn, catWin});
                        }
                    }
                }
            } else { // 上一步是貓走
                for (int prev_c : graph[c]) {
                    if (prev_c != 0 && results[m][prev_c][catTurn] == 0) {
                        // 如果這步能讓貓贏
                        if (res == catWin) {
                            results[m][prev_c][catTurn] = catWin;
                            q.push({m, prev_c, catTurn, catWin});
                        } 
                        // 如果這步是貓走，但目前結果是鼠贏，則減少貓的出度
                        else if (--degree[m][prev_c][catTurn] == 0) {
                            results[m][prev_c][catTurn] = mouseWin;
                            q.push({m, prev_c, catTurn, mouseWin});
                        }
                    }
                }
            }
        }

        return results[mouseStart][catStart][mouseTurn];
    }
};
