/*
 *  參考: https://leetcode.cn/problems/take-k-of-each-character-from-left-and-right/solutions/2928177/mei-chong-zi-fu-zhi-shao-qu-k-ge-by-leet-10ct/
 *
 *  因為是取左邊和右邊char 所以slindig window表示留下的char, 取出的char使用vector<int> cnt(3)來表示
 *  
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    int takeCharacters(string s, int k) {
        if(k == 0) return 0;
        else if(k * 3 > s.size()) return -1;

        vector<int> cnt(3, 0);
        for(auto& c : s) cnt[c - 'a']++;
        for(auto& c : cnt)
            if(c < k) return -1;
        int ans = s.size();
        
        for (int r = 0, l = 0; r < s.size(); r++) {
            cnt[s[r] - 'a']--;
            while (l < r && (cnt[0] < k || cnt[1] < k || cnt[2] < k)) { // 取出的的char不滿足
                cnt[s[l] - 'a']++;
                l++;
            }
            if (cnt[0] >= k && cnt[1] >= k && cnt[2] >= k) { // 必須滿足條件才可以判斷
                ans = min(ans, (int)s.size() - (r - l + 1));
            }
        }

        return ans;
    }
};
/*
 *  2024/11/20 daily challenge
 *  一樣的想法因為取左右 所以中間視為slinding window
 */
class Solution {
public:
    int takeCharacters(string s, int k) {
        int cur[3] = {0}, sz = s.size(), ans = sz;
        int cnt[3] = {0};
        // special case
        if(k * 3 > s.size()) return -1;
        for(auto& c : s) cnt[c - 'a']++;
        for(auto& c : cnt) {
            if(c < k) return -1;
            c -= k;
        }
        if(k * 3 == sz) return sz;
        // general case
        for(int left = 0, right = 0; right < s.size(); ++right) {
            cur[s[right] - 'a']++;
            while((left <= right) && ((cur[0] > cnt[0]) || (cur[1] > cnt[1]) || (cur[2] > cnt[2]))) {
                cur[s[left] - 'a']--;
                left++;
            }
            ans = min(ans, sz - (right - left + 1));
        }
        return ans;
    }
};
/*     |  |
    aabaaaacaabc, k = 2

    a = 8  --> 6
    b = 2  --> 0
    c = 2  --> 0

    a = 4

*/
