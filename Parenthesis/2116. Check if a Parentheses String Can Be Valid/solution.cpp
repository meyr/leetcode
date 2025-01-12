/*  參考: https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/solutions/1646594/left-to-right-and-right-to-left-by-votru-7a05/  
 *  參考: https://leetcode.cn/problems/check-if-a-parentheses-string-can-be-valid/solutions/1179134/pan-duan-yi-ge-gua-hao-zi-fu-chuan-shi-f-0s47/
 *
 *  **檢查括弧(parentheses)是否正確的實用技巧**
 *  分數計算 :
 *             0. 遇到'(' 則分數+ 1, 遇到')'則分數-1
 *             1. 最後總分要為0 才是正確的parentheses string --> 表示左右括弧的數量一樣
 *             2. 任何一個prefix(從0開始到某個位置i) 都需要滿足 __分數大於等於0__ --> 小於0 表示右括弧多於左括弧
 *                ex: (())) 分數為˙-1, 即使之後有左括弧 (()))( 還是錯的，小於0表示無法match了。
 * 
 *  解法:
 *        0. 檢查size是否為2的倍數。
 *        1. 從左掃到右 '(' : +1, ')' : -1, 最後wild >= abs(bal)
 *        2. 從右掃到左 '(' : -1, ')' : +1, 最後wild >= abs(bal), 為什麼要這樣檢查?
 *           如果只從左掃到右, 這個test case會失敗 ["))((", "0011"]
 *                                                   wild = 2, bal = 2 因為wildcard先出現，之後才出現左括弧 條件會成立
 *                                                   所以必須反過來檢查
 *
 *  time  : O(N)
 *  space : O(1)
 */
 class Solution {
    bool check_left_to_right(string& s, string& locked) {
        int bal{}, wild{}, sz = s.size();
        for(int i = 0; i < sz && bal + wild >= 0; ++i) { // __important__ bal + wild >= 0 為了滿足條件2
            if(locked[i] == '0') wild++;
            else bal += s[i] == '(' ? 1 : -1;
        }
        return wild >= abs(bal);
    }
    bool check_right_to_left(string& s, string& locked) {
        int bal{}, wild{}, sz = s.size();
        for(int i = sz - 1; i >= 0 && bal + wild >= 0; --i) {
            if(locked[i] == '0') wild++;
            else bal += s[i] == ')' ? 1 : -1;
        }
        return wild >= abs(bal);
    }

public:
    bool canBeValid(string s, string locked) {
        return s.size() % 2 == 0 && check_left_to_right(s, locked) && check_right_to_left(s, locked);
    }
};
