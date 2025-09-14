/*  有三種可以match的case
 *  case 1. 完全match 使用uswl來儲存原本的wordlist
 *  case 2. 大小寫有差 但是其他完全符合 儲存小寫case和index 使用um1
 *  case 3. vowel可以互換 把 vowel char換成* 儲存string和index 使用um2
 *
 *  time  : O(MN + QM) ,  N:size of wordlist, Q: size of queries, M: maximum size of string
 *  space : O(N + N + N) = O(N)
 */
class Solution {
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> uswl(begin(wordlist), end(wordlist));
        unordered_map<string, int> um1, um2;
        unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};
        for(int i = 0; i < wordlist.size(); ++i) { // O(N(M + M)) = O(2MN) = O(MN)
            string word = wordlist[i];
            transform(begin(word), end(word), begin(word), [](char c){
                return tolower(c);
            });
            if(!um1.count(word)) um1[word] = i;
            transform(begin(word), end(word), begin(word), [&](char c){
                if(vowels.count(c)) return '*';
                else return c;
            });
            if(!um2.count(word)) um2[word] = i;
        }
        vector<string> rtn;         // O(QM)
        for(auto q : queries) {
            if(uswl.count(q)) {
                rtn.push_back(q);
                continue;
            }
            transform(begin(q), end(q), begin(q), [](char c){
                return tolower(c);
            });
            if(um1.count(q)) {
                rtn.push_back(wordlist[um1[q]]);
                continue;
            }
            transform(begin(q), end(q), begin(q), [&](char c){
                if(vowels.count(c)) return '*';
                else return c;
            });
            if(um2.count(q)) {
                rtn.push_back(wordlist[um2[q]]);
                continue;
            }
            rtn.push_back("");
        }
        return rtn;
    }
};
