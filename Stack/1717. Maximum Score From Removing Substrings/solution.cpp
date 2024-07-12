/*
 *  參考解答 : https://leetcode.com/problems/maximum-score-from-removing-substrings/solutions/5464043/explanations-no-one-will-give-you-2-detailed-approaches-extremely-simple-and-effective/
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    int removePairs(string &s, string t) {
        int idx = 0, count = 0; // 使用idx直接在s裡面操作
        for (char c : s) {
            s[idx++] = c;
            if (idx > 1 && s[idx - 1] == t[1] && s[idx - 2] == t[0]) {
                count++;
                idx -= 2;
            }
        }
        s.resize(idx);
        return count;
    }

    int maximumGain(string s, int x, int y) {
        int res = 0;
        vector<string> p{"ab", "ba"};

        if (y > x) {    // x always greater than y
            swap(p[0], p[1]);
            swap(x, y);
        } 

        res += removePairs(s, p[0]) * x;
        res += removePairs(s, p[1]) * y;
        return res;
    }
};
