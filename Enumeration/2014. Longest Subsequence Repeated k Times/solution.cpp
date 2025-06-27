/*  ref : https://leetcode.com/problems/longest-subsequence-repeated-k-times/solutions/1474122/insights-and-optimizations-by-votrubac-abln/
 *
 *  為什麼這題是Enumeration(列舉)題目? 
 *
 *  如果ans的subsequence的程度為S 則重複k次拼起來的長度為 S * K
 *  constraints跟我們說 8 * K > n, 所以S只要大於8就會超過n, 那S最大值就是7
 *  因為ans最長為7, 如果我們知道某些charset才有可能組成subsequence(也就是freq[c] >= k)
 *  那麼就是"列舉"所以可能的答案, 並解檢查是否符合答案
 *
 *  這邊是要求longest lexicographically largest subsequence.
 *
 */
class Solution {
public:
    bool check(string &s, string &p, int k) {
        //  i 指向 s
        //  j 指向 p
        for (int i = 0, j = 0; i < s.size() && k > 0; ++i) {
            j += p[j] == s[i];
            if (j == p.size()) {
                --k;
                j = 0;
            }
        }
        return k == 0;
    }
    /*
     *  chars : 可以使用的char set
     *  cur   : 目前ans的subsequence
     *  best  : 目前最佳的解答
     *  mask  : 使用過的char
     */
    void generate(string &s, string &chars, string &cur, string &best, int mask, int k) {
        for (int i = 0; i < chars.size(); ++i) {
            if ((mask & (1 << i)) == 0) {   //  此char沒使用過
                string new_cur = cur + chars[i];
                cout << new_cur << endl;
                if (check(s, new_cur, k)) {
                    if (new_cur.size() > best.size())   //  因為new_string是根據lexicographically largest排列過，所以只須比較長度
                        best = new_cur;
                    generate(s, chars, new_cur, best, mask | (1 << i), k);
                }
            }
        }
    }
    string longestSubsequenceRepeatedK(string &s, int k) {
        int cnt[26] = {};
        string chars, best;
        for (auto ch : s)
            ++cnt[ch - 'a'];
        for (int i = 25; i >= 0; --i)               // 由大到小? 因為題目要求lexicographically largest
            chars += string(cnt[i] / k, 'a' + i);

        generate(s, chars, string() = {}, best, 0, k);
        return best;
    }
};
