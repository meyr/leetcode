/*  參考解答
 *
 *  首先 lexicographically largest string  開頭一定是string word中最大的char
 *                                         如果兩個str1, str2前n個char一樣 則長度較長的會比較大
 *                                         如果兩個str1, str2第二個char不一樣 則不管長短都會以第二的char最大為 LLS
 *
 *                                         Greedy point: 取最長的string來比較
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    string answerString(string_view word, int numFriends) {
        if(numFriends == 1) return string(word);
        int maxlen = word.size() - numFriends + 1;
        string_view ans{};
        char maxchar{};
        for(int i = 0; i < word.size(); ++i) {
            maxchar = max(maxchar, word[i]);
            if(word[i] >= maxchar)
                ans = max(ans, word.substr(i, min(maxlen, (int)word.size() - i)));      // __important__ 取最長長度卻不超過word.size()
        }
        return string(ans);
    }
};
