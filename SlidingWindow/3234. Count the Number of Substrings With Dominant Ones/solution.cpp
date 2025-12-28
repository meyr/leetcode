/*  參考 : https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/solutions/5546675/on-sqrt-n-by-votrubac-fz3c/
 * 
 *   一個stirng 長度為N, 裡面有zcnt和ocnt
 *   zcnt + ocnt = N
 *   因為 1-dominated string 必須滿足 ocnt >= zcnt * zcnt
 *   ocnt = N - zcnt
 *   ocnt = N - zcnt >= zcnt * zcnt
 *   zcnt + zcnt * zcnt <= N --> 必須滿足才是1-dominated string
 *
 *   所以可以根據zcnt和s.size()來決定需要尋找的次數 O(sqrt(N))
 *
 *   且滿足 ocnt >= zcnt * zcnt, 則onct - zcnt * zcnt >= 0
 *   等於0是剛好滿足, 如果是 > 0 就是多出來的餘裕
 *
 *   left, ... prev(first '0'), ... right
 *   1. prev - left = 從第一個0往左延伸有多少個'1'
 *   2. ocnt - zcnt * zcnt 為多出來的'1'
 *   所以我們固定了right, 則從prev往左延伸可以多出來的substring為
 *   1 + min(prev - left, ocnt - zcnt * zcnt), 這邊的1是[prev, left]還沒包刮'1'的substring
 *
 */
class Solution {
public:
    int numberOfSubstrings(string s) {
        int res{};
        for(int zcnt = 0; zcnt + zcnt * zcnt <= s.size(); ++zcnt) {
            int cnt[2] = {}, prev = 0, old_res = res;
            // slinding window是保持window中有固定zcont的'0'
            for(int right = 0, left = 0; right < s.size(); ++right) {
                ++cnt[s[right] == '1']; // 統計'0'和'1'的數量
                while(cnt[0] > zcnt) --cnt[s[left++] == '1'];
                // 此window滿足條件
                if(cnt[0] == zcnt && cnt[1] && cnt[1] >= zcnt * zcnt) {
                    //找出left之後第一個出現的'0' ??
                    for(prev = max(prev, left); prev < right && s[prev] == '1'; ++prev);
                    res += 1 + min(prev - left, cnt[1] - zcnt * zcnt);
                }
            }
        }
        return res;
    }
};
/* 參考 : 官方解答
 *        https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/solutions/7338477/count-the-number-of-substrings-with-domi-jqas/
 *       
 *  
 */
 class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        vector<int> pre(n + 1); // 前一個'0'的位置
        pre[0] = -1;
        for (int i = 0; i < n; i++) {
            if (i == 0 || (i > 0 && s[i - 1] == '0')) {
                pre[i + 1] = i;
            } else {
                pre[i + 1] = pre[i];
            }
        }
        int res = 0;
        for (int i = 1; i <= n; i++) {
            int cnt0 = s[i - 1] == '0';
            int j = i; // 從i 開始往左跳到前一個'0'
            while (j > 0 && cnt0 * cnt0 <= n) {
                int cnt1 = (i - pre[j]) - cnt0; // 計算'1'數量
                if (cnt0 * cnt0 <= cnt1) { // 滿足1-dominated
                    res += min(j - pre[j], cnt1 - cnt0 * cnt0 + 1);
                }
                j = pre[j];
                cnt0++;
            }
        }
        return res;
    }
};
