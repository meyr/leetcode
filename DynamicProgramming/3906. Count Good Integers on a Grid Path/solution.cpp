/*
 * 參考: https://leetcode.com/problems/count-good-integers-on-a-grid-path/solutions/7990326/javacpython-dp-by-lee215-i80i/
 */
class Solution {
    unordered_set<int> pos;
    long long memo[17][11][2];

    /*   i : 目前的index
     * prev: 上一個路徑上的數值 因為我們要比上一個還要大於等於 產生non-decreasing
     *    t: 數字是否沿著邊界數值走
     */
    long long helper(const string& str, int i, int prev, int t)
    {
        if (i == str.size()) return 1;
        if(~memo[i][prev][t]) return memo[i][prev][t];
        long long res = 0;
        int lim = t ? (str[i] - '0') : 9; // t == 1, 上一個數字是沿著邊界數字 為了不超過 這個不能大於等於str[i]
        for (int x = 0; x <= lim; ++x) {
            if (pos.count(i)) {           // 在路徑上
                if (x >= prev)            // 選擇的數字要大於等於 prev
                    res += helper(str, i + 1, x, t && (x == lim));  // t && (x == lim)  上一個數字沿著邊界 且這個數字剛好也是邊界
            } else {
                res += helper(str, i + 1, prev, t && (x == lim));
            }
        }
        return memo[i][prev][t] = res;
    }
public:
    long long countGoodIntegersOnPath(long long l, long long r, string directions) {
        int cur = 0;
        pos.insert(0);
        for(const auto& d : directions) {   // 紀錄會經過的position
            cur += d == 'D' ? 4: 1;
            pos.insert(cur);
        }

        string tmp = to_string(l - 1);      // __important__ 包括left所以要計算 f(r) - f(l - 1)
        string strl = string(16 - tmp.size(), '0') + tmp;
        tmp = to_string(r);
        string strr = string(16 - tmp.size(), '0') + tmp;

        memset(memo, -1, sizeof(memo));
        long long ll = helper(strl, 0, 0, 1);
        memset(memo, -1, sizeof(memo));
        long long rr = helper(strr, 0, 0, 1);
        return rr - ll;
    }
};

