/*  寫了很多次才AC 沒辦法一次就寫出正確答案 很多眉角需要注意
 *
 *  __important__ rotate 90 clockwise (y, x) --> (x, m - y - 1)
 *
 *  time  : O(MN + MNM) = O(NM^2)
 *  space : O(MN)
 */
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size(), n = boxGrid[0].size();
        vector<vector<char>> rtn(n, vector<char>(m, '.'));
        unordered_map<int, int> mp;
        for(int y = 0, count = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                count += boxGrid[y][x] == '#';
                if(boxGrid[y][x] == '*') {
                    rtn[x][m - y - 1] = '*';
                    mp[(x - 1) * m + (m - y - 1)] = count; // 統計旋轉後這個block上面會有多少個'#'
                    count = 0;
                }
            }
            if(count) {
                mp[(n - 1) * m + (m - y - 1)] = count;  // 統計旋轉後最底部上面會有多少個'#'
                count = 0;
            }
        }

        for(int y = n - 1; y >= 0; --y) {
            for(int x = 0; x < m; ++x) {
                if(mp.count(y * m +  x)) {   // 上面有'#' 依序填入
                    int cnt = mp[y * m + x];
                    int prevy = y;
                    while(cnt--)
                        rtn[prevy--][x] = '#';
                }
            }
        }
        return rtn;
    }
};
/* 參考官方解答
 * 使用two pointer, 一行一行掃描從最底開始
 * 使用lowestRowWithEmptyCell 來記錄目前最底的x是哪一個
 *
 * time  : O(MN)
 * space : O(MN)
 */
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int m = box.size();
        int n = box[0].size();
        vector<vector<char>> result(n, vector<char>(m, '.'));

        // Apply gravity to let stones fall to the lowest possible empty cell in
        // each column
        for (int i = 0; i < m; i++) {
            int lowestRowWithEmptyCell = n - 1;
            // Process each cell in row `i` in reversed order
            for (int j = n - 1; j >= 0; j--) {
                // Found a stone - let it fall to the lowest empty cell
                if (box[i][j] == '#') {
                    // Place it in the correct position in the rotated grid
                    result[lowestRowWithEmptyCell][m - i - 1] = '#';
                    // (Optional - already initialized to '.') result[j][m - i -
                    // 1] = '.';
                    lowestRowWithEmptyCell--;
                }
                // Found an obstacle - reset `lowestRowWithEmptyCell` to the row
                // directly above it
                if (box[i][j] == '*') {
                    // Place the obstacle in the correct position in the rotated
                    // grid
                    result[j][m - i - 1] = '*';
                    lowestRowWithEmptyCell = j - 1;
                }
            }
        }
        return result;
    }
};
