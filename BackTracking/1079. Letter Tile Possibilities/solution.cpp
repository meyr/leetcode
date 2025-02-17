/* 參考解答: https://leetcode.com/problems/letter-tile-possibilities/solutions/381605/c-0-ms-runtime-100-by-oshyman-5jnj/
 * 
 * 這類題目很苦手
 *
 * A, B, C, _   <-- 假設前面已經有三個char, 則第四個可以放什麼? 當然是從vector<int> cnt選擇一個(從剩下的字母中選一個)
 * A, B, C, A   <-- 選完之後更新vector<int> cnt, 只要cnt != 0就繼續
 * A, B, C, B   <-- 從helper() return回來之後 繼續選下一個 for(int i = 0; i < cnt.size(); ++i) 使用for loop保證不會選擇相同字母會跳下一個
 *
 */
class Solution {
    void helper(vector<int>& cnt, int& rtn)  {
        for(int i = 0; i < cnt.size(); ++i) { 
            if(cnt[i]) {
                cnt[i]--;
                rtn++;
                helper(cnt, rtn);
                cnt[i]++;
            }
        }
    }
public:
    int numTilePossibilities(string tiles) {
        vector<int> cnt(26);
        for(auto& c : tiles) cnt[c - 'A']++;
        int rtn{};
        helper(cnt, rtn);
        return rtn;
    }
};
