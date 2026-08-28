/*
 *      類似 2904. Shortest and Lexicographically Smallest Beautiful String
 *      但是這次是要組成palindrome
 *
 *      因為要達到palindrome所以我們只需要組前半 後半就是前半的reverse
 *
 *      time  : O(26^(N/2))   每次都要跑26個字母 但是只需要檢查N/2
 */
class Solution {
    vector<int> count = vector<int>(26);
    int odds{}, oddidx{-1};
    string ans{};
    bool helper(string_view target, int idx, bool is_greater) {
        if(idx >= target.size() / 2) {                              // 達到一半 後半用拼的
            string tmp;
            if(target.size() % 2)                                   // 如果是奇數 放入一個中間點
                tmp += oddidx + 'a';
            tmp += ans;
            reverse(begin(tmp) + (target.size() % 2), end(tmp));    // 反轉原本的string 如果是奇數 跳過第一個字元

            string tmpans(ans);
            tmpans += tmp;
            if(tmpans > target) {                                   // 檢查最終結果是否大於target
                ans = move(tmpans);
                return true;
            } else return false;
        } else {
            int start = is_greater ? 0 : target[idx] - 'a';         // 如果已經比target大了 就可以從'a'開始 這樣才可以得到Lexicographically Smallest
            for(int i = start; i < 26; ++i) {
                if(count[i] >= 2) {                                 // __important__ 因為我們要預留後面的char 所以最少要兩個以上
                    ans.push_back(i + 'a');
                    count[i]-=2;
                    if(helper(target, idx + 1, is_greater ? 1 : i + 'a' > target[idx]))
                        return true;
                    count[i]+=2;
                    ans.pop_back();
                }
            }
            return false;
        }
    }
public:
    string lexPalindromicPermutation(string s, string target) {
        for(auto& c : s) count[c - 'a']++;
        for(int i = 0; i < 26; ++i){
            if(count[i] % 2) {
                odds++;
                oddidx = i;
            }
        }
        if(odds > 1 || (odds == 1 && target.size() % 2 == 0))
            return "";
        auto rtn = helper(target, 0, 0);
        if(rtn) return ans;
        else return "";
    }
};
