/*
 *  參考 : https://leetcode.com/problems/get-equal-substrings-within-budget/solutions/392857/c-java-sliding-window-o-n-o-1/
 *  
 *  也是使用slinding window 但是同時計算兩個char的cost 同時計算substring大小
 *  這邊比較奇怪的是為什麼只用if判斷
 *
 *  time  : O(N)
 *  space : O(1) 
 */
class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int left = 0, right = 0;
        while(right < s.size()) {
            maxCost -= abs(s[right] - t[right++]);
            if(maxCost < 0) maxCost += abs(s[left] - t[left++]);
        }
        return right - left;
    }
};
