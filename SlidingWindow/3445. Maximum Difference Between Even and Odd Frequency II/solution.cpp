/*  參考解答 : https://leetcode.cn/problems/maximum-difference-between-even-and-odd-frequency-ii/solutions/3694397/qi-ou-pin-ci-jian-de-zui-da-chai-zhi-ii-vnz1n/
 *  和使用AI解說
 *
 */
class Solution {
public:
    int maxDifference(string s, int k) {
        auto getStatus = [](int cnt_a, int cnt_b) -> int {  // 取得a, b的奇偶排列, 00(偶偶), 01(偶奇), 10(奇偶), 11(奇奇)
            return ((cnt_a & 1) << 1) | (cnt_b & 1);
        };

        int n = s.size();
        int ans = INT_MIN;
        for (char a = '0'; a <= '4'; ++a) {         // 因為char只有[0, 1, 2, 3, 4] 所以列舉所有a, b的可能性[0, 1][0, 2][0, 3][0, 4][1, 0][1, 2][1, 3][1, 4]
            for (char b = '0'; b <= '4'; ++b) {     //                                                   [2, 0][2, 1][2, 3][2, 4][3, 0][3, 1][3, 2][3, 4]
                if (a == b) {                       //                                                   [4, 0][4, 1][4, 2][4, 3]
                    continue;                       // 跳過 a == b的情況
                }
                int best[4] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX}; // 紀錄left掃過去後每種奇偶排列的最小 prev_a - prev_b ==> max((cnt_a - prev_a) - (cnt_b - prev_b)) = max((cnt_a - cnt_b) - (prev_a - prev_b))
                                                                    //                                                                                                       ^^^^^^^^^^^^^^^   ^^^^^^^^^^^^^^^^^ 選遇過的最小值
                                                                    //                                                                                                       目前的現況無法改變
                int cnt_a = 0, cnt_b = 0;           // 計算從0-right, a 出現的頻率(cnt_a) 和 b出現的頻率 (cnt_b)        一個substring中 a出現頻率(cnt_a - prev_a), 
                int prev_a = 0, prev_b = 0;         // 計算從0-left, a 出現的頻率(prev_a) 和 b出現的頻率 (prev_b)                       b出現頻率(cnt_b - prev_b)
                int left = -1;
                for (int right = 0; right < n; ++right) {
                    cnt_a += (s[right] == a);
                    cnt_b += (s[right] == b);
                    while (right - left >= k && cnt_b - prev_b >= 2) {  // cnt_b - prev_b 表示substring中的b頻率，因為 =0(沒有b，不成立), =1(奇數，不成立)
                        int left_status = getStatus(prev_a, prev_b);
                        best[left_status] = min(best[left_status], prev_a - prev_b);
                        ++left;
                        prev_a += (s[left] == a);
                        prev_b += (s[left] == b);
                    }
                    int right_status = getStatus(cnt_a, cnt_b);
                    if (best[right_status ^ 0b10] != INT_MAX) { // 目前奇偶排列，找出之前 (a不同奇偶)(b相同奇偶) 的最小值
                        ans = max(ans, cnt_a - cnt_b - best[right_status ^ 0b10]); // 00(偶偶) ^ 10 = 10(奇偶)     也就是 ^10 之後前面a反向，b同向
                    }                                                              // 01(偶奇) ^ 10 = 11(奇奇)
                }                                                                  // 10(奇偶) ^ 10 = 00(偶偶)
            }                                                                      // 11(奇奇) ^ 10 = 01(偶奇)
        }
        return ans;
    }
};
/*  我使用的方法 TLE
 *  只使用prefix sum來暴力破解每個substring
 */
class Solution {
public:
    int maxDifference(string s, int k) {
        int sz = s.size();
        vector<vector<int>> cnt(5, vector<int>(sz + 1));
        for(int i = 1; i <= sz; ++i) {
            for(int c = 0; c < 5; ++c)
                cnt[c][i] = cnt[c][i - 1];
            cnt[s[i - 1] - '0'][i]++;
        }
        int rtn{INT_MIN};
        for(int left = 0; left <= s.size() - k; ++left) {
            for(int right = left + k - 1; right < s.size(); ++right) {
                int odd{}, even = sz;
                for(int c = 0; c < 5; ++c) {
                    int val = cnt[c][right + 1] - cnt[c][left];
                    if(val > 0) {
                        if(val % 2) odd = max(odd, val);
                        else even = min(even, val);
                    }
                }
                if(even != sz && odd != 0)
                    rtn = max(rtn, odd - even);
            }
        }
        return rtn;
    }
};
