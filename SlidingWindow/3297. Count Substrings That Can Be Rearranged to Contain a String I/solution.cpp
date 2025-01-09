/*  參考 : https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-i/solutions/5818284/sliding-window-with-example-walkthrough-udkc4/
 *  3298. Count Substrings That Can Be Rearranged to Contain a String II 解法也是一樣
 *
 *  自己有寫出來slinding window的解 但是計算ans的地方錯掉了 我使用 ans += left + 1 會有重複且答案也是錯的
 *
 *     0, 1, 2, 3, 4, 5, 6, 7, 8
 *     d, c, b, d, c, d, c, c, b
 *     |        |                  --> [dcbd]
 *        |           |            --> [dcbdcd][cbdcd]
 *           |        |            --> [dcbdcd][cbdcd][bdcd]
 *              |     |            --> [dcbdcd][cbdcd][bdcd][dcd]
 *
 *
 *  應該是如下的解釋 以left為頭 right以後的substring都符合
 *
 *     0, 1, 2, 3, 4, 5, 6, 7, 8
 *     d, c, b, d, c, d, c, c, b
 *     |        |                  --> [dcbd][dcbdc][dcbdcd][dcbdcdc][dcbdcc][dcbdccb]
 *        |           |            --> [cbdcd][cdbcdc][cdbcdcc][cdbcdccb]
 *           |        |            --> [bdcd][bdcdc][bdcdcc][bdcdccb]
 *              |     |            --> [dcd][dcdc][dcdcc][dcdccb]

 *
 *  time  : O(N + M)    , N : size of word1, M : size of word2
 *  space : O(1)
 */
class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        unordered_map<char, int> m1, m2;
        for(const auto& c : word2) m2[c]++;
        long long ans{};
        int cnt = m2.size();
        for(int left = 0, right = 0; right < word1.size(); ++right) {
            char& c = word1[right];
            if(m2.count(c) && m1[c] == m2[c] - 1) cnt--;
            m1[c]++;
            while(cnt == 0) {
                ans += word1.size() - right;    // __important__ 找到符合的[left, right]之後表示裡面包含word2, 以left為開頭到word1.size()的substring皆符合 
                char& c = word1[left++];
                if(m2.count(c) && m1[c] == m2[c]) cnt++;
                m1[c]--;
            }
        }
        return ans;
    }
};
