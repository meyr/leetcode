/*
 * 直接參考lee215大神的答案 : https://leetcode.com/problems/spiral-matrix-iii/solutions/158970/c-java-python-1-1-2-2-3-3-steps/
 * 非常漂亮的解答
 *
 * time  : O(max(R, C)^2) : 最大邊的平方
 * space : O(RC)
 */
class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int R, int C, int r, int c) {
        vector<vector<int>> res = {{r, c}};
        int dx = 0, dy = 1, tmp;
        for (int n = 0; res.size() < R * C; n++) { // 0, 1, 2, 3, 4, 5, ...
            for (int i = 0; i < n / 2 + 1; i++) {  // 1, 1, 2, 2, 3, 3, ...
                r += dx, c += dy;
                if (0 <= r && r < R && 0 <= c && c < C) // 走出外面的讓它繼續走，直到走回裡面
                    res.push_back({r, c});              // 這樣可以避免需要判斷走出grid後的下個點
            }
            tmp = dx, dx = dy, dy = -tmp; // turn right
        }
        return res;
    }
};
/*
    本來的方向是(0, 1) ->(1, 0)->(0, -1)->(-1, 0)
    可以推論出 (x, y) -> (y, -x)

*/
