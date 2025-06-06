/*  參考: https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/solutions/2678810/counter-by-votrubac-gat4/
 *
 *  lexicographically smallest string --> Greedy point 一定是先印出最小的char
 *  例如：　s="bydizfve"  --> 最小的char是'b'
 *
 *          s="ydizfve"  --> 接下來最小的是'd' 但是我們為了印出d 所以必須先走訪到'd', 在'd'之前的需要先放在string t
 *
 *          s = "izfve", t = "yd"  --> 印出'd'
 *          s = "izfve", t = "y"  --> 接下來最小的是'e', 為了印出'e'我們需要把'e'前面的都放到t
 *          s = "", t = "yizfve"  --> 印出'e'
 *          s = "", t = "yizfv"   --> 因為s已經清空 所以全部印出
 *
 *  time  : O(N)
 *  space : O(N)
 *
 */
class Solution {
public:
    string robotWithString(string s) {
        vector<int> cnt(26);        // 統計string s所有char的個數
        for(auto& c : s)
            cnt[c - 'a']++;
        string t{}, p{};
        int idx{};
        for(auto& c : s) {
            t.push_back(c);
            cnt[c - 'a']--;
            while(idx < 26 && cnt[idx] == 0) ++idx;         // __important__ 找出目前string s中最小的char
            while(!t.empty() && (t.back() - 'a') <= idx) {  // t.back() == idx, 印出最小char
                p.push_back(t.back());                      // t.back() < idx 因為string s中剩下的都比t.back()還大 所以印出
                t.pop_back();
            }
        }
        return p;
    }
};
