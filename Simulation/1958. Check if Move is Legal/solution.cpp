/*
 *  time  : O(N + M)
 *  space : O(1) 
 */

class Solution {
    int m, n;
    bool inBoard(int y, int x) {
        return y < m && x < n && y >= 0 && x >= 0;
    }
public:
    bool checkMove(vector<vector<char>>& board, int rMove, int cMove, char color) {
        m = board.size(), n = board[0].size();
        vector<vector<int>> steps{{0, 1}, {0, -1}, {1, 0}, {-1, 0},
                                  {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        int t = color == 'B' ? 'W' : 'B';
        for(auto& step : steps) {
            int y = rMove + step[0]; // 先檢查下一個點是否為反向顏色
            int x = cMove + step[1];
            if(!inBoard(y, x) || board[y][x] != t) continue;
            y += step[0]; // 再取下一個點
            x += step[1];
            while(inBoard(y, x)) {
                if(board[y][x] == '.') break; // 不是good line
                else if(board[y][x] == color) return true; // 相同顏色即為good line的endpoint
                y += step[0]; // 相反顏色繼續前進
                x += step[1];
            }
        }
        return false;
    }
};
