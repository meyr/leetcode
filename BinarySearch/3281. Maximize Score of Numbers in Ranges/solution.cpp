/*
    ans    : 1, 2, [3], 4, 5, 6  間格越小越容易找到  
    result : T, T,  T , F, F, F

    [0, 3, 6]

    cur = 0, mid = 4
    [3, 4, 5]
        4

*/
class Solution {
public:
    int maxPossibleScore(vector<int>& start, int d) {
        sort(begin(start), end(start));
        int left = 0, right = ((start.back() + d - start.front()) / (start.size() - 1)) + 1; // 必須+1才可以驗證到 最大區間
        while(left < right) {
            long mid = left + (right - left) / 2;
            int result{1};
            long cur = start[0];
            for(int i = 1; i < start.size(); ++i) {
                if(cur + mid > start[i] + d) { // 如果下一個值在目前的區間找不到 則離開
                        result = 0;
                        break;
                }
                cur = max((long)start[i], cur + mid); //                     [x, x+1, x+2, x+3]
            }                                         // 有兩種可能          [x, x+1, cur+mid, x+2, x+3]  選 cur+mid
            if(result) left = mid + 1;                //           [cur+mid] [x, x+1, x+2, x+3]           選 x
            else right = mid;                         // 所以選擇 max(cur+mid, x)
        }
        return left - 1;
    }
};
