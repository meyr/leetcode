/*
 *      一開始我寫了以下的code
 *      但是有錯,因為這樣的假設是兩個都是rect
 *      因為circle四邊都是有缺角的,這樣會有問題
 */
 class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        auto isOverlap = [](int x1, int y1, int x2, int y2) {
            return max(x1, x2) <= min(y1, y2);
        };
        return isOverlap(x1, x2, xCenter - radius, xCenter + radius) &&
               isOverlap(y1, y2, yCenter - radius, yCenter + radius);
    }
};
/*
 *      參考gemini的解答
 *      找出rect中最靠近circle的點
 *      確認這個點是否在圓裡面
 */
class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        // 找出rect內最靠近circle的點
        int cx = clamp(xCenter, x1, x2);
        int cy = clamp(yCenter, y1, y2);
        // 這個點算出汗xCenter, yCenter的距離
        int dx = cx - xCenter;
        int dy = cy - yCenter;
        int dist = dx * dx + dy * dy;
        // 如果距離小於等於radius表示在圓裡面
        return dist <= radius * radius; 
    }
};
