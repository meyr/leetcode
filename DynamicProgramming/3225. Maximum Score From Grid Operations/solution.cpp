/*  參考gemeni pro解答
 *
 *  目前高度和前一個欄位高度可以有兩種組合 1. 下降 ---+      2. 上升      +---   如果只考慮兩個column不管是上升或是下降 都可以吃掉高度差的數值
 *                                                    |                   |
 *                                                    +---             ---+
 *                                                                                                                                         +---
 *  但是考慮三個欄位就會有四種組合  1. 下降-下降  ---+        2. 下降-上升  ---+          3. 上升-下降     +---+      4. 上升-上升         |
 *                                                   |                         |   +---                    |   |                       +---+
 *                                                   +---+                     |   |                       |   +---                    |
 *                                                       |                     +---+                    ---+                        ---+
 *                                                       +---
 *                                                        c                          c                           c                           c
 *  除了2. 下降-上升會重複計算之外 其他都可以把分數吃掉
 *  目前的column有三個行為 1. 把前一個分數吃掉 2. 把現在的分數出掉  3. 目前的分數不吃給下一欄吃
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    int n;
    // prefix[c][h] 代表第 c 欄，前 h 個格子的分數總和
    vector<vector<long long>> prefix;

    // memo[c][prev_h][is_prev_eaten]
    vector<vector<vector<long long>>> memo;

    // 遞迴函式：計算從第 c 欄到最後一欄所能獲得的最大分數
    //
    // 參數說明：
    // - c: 當前正在處理的欄位 index
    // - prev_h: 左邊那一欄 (c-1) 塗黑的高度
    // - is_prev_eaten: 左邊那一欄 (c-1) 的白格，是否已經「被更左邊 (c-2)」吃掉計分了？
    //   -> 0 代表「沒被吃」，所以當前欄 c 可以往左吃它。
    //   -> 1 代表「已被吃」，所以當前欄 c 絕對不能再往左吃它（避免重複計分）。
    long long solve(int c, int prev_h, int is_prev_eaten) {
        if (c == n) return 0;
        if (memo[c][prev_h][is_prev_eaten] != -1) return memo[c][prev_h][is_prev_eaten];

        long long max_score = 0;

        for (int curr_h = 0; curr_h <= n; ++curr_h) {

            if (curr_h > prev_h) {  // case 2, case 4 只有前面沒被吃掉才可以吃
                if (is_prev_eaten == 0) {
                    long long score = prefix[c - 1][curr_h] - prefix[c - 1][prev_h];
                    // 因為是吃掉前一欄，傳遞 0 (沒被吃) 給下一層，允許未來的 c+1 往左吃掉當前欄 c。
                    max_score = max(max_score, score + solve(c + 1, curr_h, 0));
                }
            }
            else {  // case 1, case 3 可以直接吃掉當前欄位 或是選擇不吃
                long long score = prefix[c][prev_h] - prefix[c][curr_h];

                // 決策 1：拿走這筆分數 (Pick)
                // 傳遞 1 (已被吃) 給下一層，警告未來的 c+1 絕對不能再往左吃 c。
                max_score = max(max_score, score + solve(c + 1, curr_h, 1));

                // 決策 2：忍住不拿這筆分數 (Skip)
                // 傳遞 0 (沒被吃) 給下一層，允許未來的 c+1 往左吃掉當前欄 c。
                max_score = max(max_score, solve(c + 1, curr_h, 0));
            }
        }

        return memo[c][prev_h][is_prev_eaten] = max_score;
    }

public:
    long long maximumScore(vector<vector<int>>& grid) {
        n = grid.size();

        prefix.assign(n, vector<long long>(n + 1, 0));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                prefix[j][i + 1] = prefix[j][i] + grid[i][j];
            }
        }

        memo.assign(n, vector<vector<long long>>(n + 1, vector<long long>(2, -1)));

        long long ans = 0;

        // 第 0 欄沒有「左邊那一欄」，我們直接枚舉第 0 欄的高度 h0，然後從第 1 欄開始計算。
        for (int h0 = 0; h0 <= n; ++h0) {
            // 傳入的初始狀態為 0，因為第 0 欄絕對不可能「被更左邊吃掉」(根本沒有更左邊)。
            ans = max(ans, solve(1, h0, 0));
        }

        return ans;
    }
};
