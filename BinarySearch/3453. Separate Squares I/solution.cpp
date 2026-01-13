/*
 *  直覺使用binary search 但是邊界是double必須注意 float, double所表示的數不是連續
 *  只要精準度小於1e-5就可以停下來
 *
 */
class Solution {
    enum position{
        x, y, l
    };
public:
    double separateSquares(vector<vector<int>>& squares) {
        double bottom = 1e9, top = 0;
        for(auto& s : squares) {
            bottom = min(bottom, (double)s[y]);
            top = max(top, (double)s[y] + s[l]);
        }
        double prev_mid{LLONG_MAX};
        while(bottom < top) {
            double mid = bottom + (top - bottom) / 2.0;
            double values{};
            for(auto& s : squares) {
                if(mid >= s[y] + s[l]) values -= (double)s[l] * s[l];
                else if(mid <= s[y]) values += (double)s[l] * s[l];
                else values += (s[y] + s[l] - mid) * s[l] - (mid - s[y]) * s[l];
            }

            if(values <= 0.0) top = mid;
            else bottom = mid + 1/1e6;

            if(abs(prev_mid - mid) <= 1/1e5) break; // 因為使用double有可能會停不下來 所以和之前的prev_mid比較
            else prev_mid = mid;                    // 小於題目要求的精準度 1/1e5 就不用計算了
        }
        return bottom;
    }
};
/*
    (s[y] + s[l] - mid) - (mid - s[y])
    s[y] + s[l] - mid - mid + s[y]

    values :   3, 2, 1, 0, 0, 0, -1, -2, -3
                     >  <=
*/
