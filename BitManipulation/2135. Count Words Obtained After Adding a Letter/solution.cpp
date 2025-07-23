/*  因為"No letter occurs more than once in any string of startWords or targetWords" 所以可以使用bitmask來統計
 *
 *  time  : O(M + N)
 *  space : O(M + N)
 */
class Solution {
    unordered_map<int, unordered_set<int>> um;
    int getHash(const string& word) {
        int hash{};
        for(auto& c : word)
            hash |= 1 << (c - 'a');        
        return hash;
    }
public:
    int wordCount(vector<string>& startWords, vector<string>& targetWords) {
        for(int i = 0; i < targetWords.size(); ++i) // O(M)
            um[getHash(targetWords[i])].insert(i);
        unordered_set<int> ans;
        unordered_set<int> seen;
        for(auto& word : startWords) { // O(N)
            int hash = getHash(word);
            if(seen.count(hash)) continue;
            for(int i = 0; i < 26; ++i) {
                if((hash & (1 << i)) == 0) {
                    int newval = hash | (1 << i);
                    ans.insert(begin(um[newval]), end(um[newval]));
                }
            }
            seen.insert(hash);
        }
        return ans.size();
    }
};
/*  和上面的想法一樣 但是反過來做 執行效果比較好  
 *
 *
 */
class Solution {
    int getHash(const string& word) {
        int hash{};
        for(auto& c : word)
            hash |= 1 << (c - 'a');
        return hash;
    }
    unordered_set<int> us;
public:
    int wordCount(vector<string>& startWords, vector<string>& targetWords) {
        for(auto& word: startWords)
            us.insert(getHash(word));
        int ans{};
        for(auto& word : targetWords) {
            int hash = getHash(word);
            for(int i = 0; i < 26; ++i) {
                if((hash & (1 << i)) != 0) {
                    int newhash = hash ^ (1 << i);
                    if(us.count(newhash)) {
                        ans++;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};
