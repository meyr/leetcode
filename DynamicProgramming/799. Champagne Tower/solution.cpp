/*  ref : https://leetcode.com/problems/champagne-tower/solutions/1818207/c-detailed-explanation-w-recursion-to-me-q6sp/
 *  
 *  問題是詢問(r, g)這個杯子會有多少香檳。
 *  這個杯子的香檳是由(r-1, g-1)和(r-1, g)這兩個杯子決定
 *  因為是post-order 所以 poured會被傳到r=0, g=0才開始
 *  每個杯子都會留下1之後分成兩半往左右流下去
 *
 *  time  : O(RG)
 *  space : O(RG)
 */
 class Solution {
public:
    double t[101][101]; // declaring 2 d array, to store some already computed results
    double solve(int poured, int row, int glass)
    {
        if(row < 0 || glass > row || glass < 0) return 0.00;        // 超出範圍
        if(row == 0 && glass == 0) return poured;                   // 在r=0 g=0到下poured的香檳
        if(t[row][glass] > -1) return t[row][glass];
        auto left = (solve(poured, row - 1, glass - 1) - 1) / 2;    // 左邊留下1 其他往左右兩側下流
        if(left < 0) left = 0;                                      // 沒有從上面流下來
        auto right = (solve(poured, row - 1, glass) - 1) / 2;       // 右邊留下1 其他往左右兩側下流
        if(right < 0) right = 0;                                    // 沒有從上面流下來
        auto total = left + right;
        return t[row][glass] = total;
    }
    double champagneTower(int poured, int query_row, int query_glass) {
        memset(t, -1, sizeof(t));
        return min(1.00, solve(poured, query_row, query_glass));
    }
};
