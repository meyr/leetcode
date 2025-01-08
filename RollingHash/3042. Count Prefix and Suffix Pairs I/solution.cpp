/*  一開始使用暴力破解
 *
 *  time  : O(N^2)
 *  space : O(1)
 */
class Solution {
    bool isPrefixAndSuffix(string& str1, string& str2) {
        if(str1.size() > str2.size()) return false;
        int i = 0, j = str2.size() - str1.size(), k = 0;
        while(k < str1.size()) {
            if(str1[k] != str2[i] || str1[k] != str2[j]) return false;
            i++;
            k++;
            j++;
        }
        return true;
    }
public:
    int countPrefixSuffixPairs(vector<string>& words) {
        int ans{};
        for(int i = 0; i < words.size(); ++i)
            for(int j = 0; j < i; ++j)
                ans += isPrefixAndSuffix(words[j], words[i]);
        return ans;
    }
};
/*  把遇見的string分析prefix和subfix建立hash table
 *
 *  time  : O(NM)
 *  space : O(NM)
 */
class Solution {
public:
    int countPrefixSuffixPairs(vector<string>& words) {
        int ans{};
        unordered_map<string, int> m; // string, count
        for(int i = words.size() - 1; i >= 0; --i) {
            string& str = words[i];
            ans += m[str];
            int sz = str.size();
            for(int len = 1; len <= sz; ++len) {
                if(str.substr(0, len) == str.substr(sz - len))
                    m[str.substr(0, len)]++;
            }
        }
        return ans;
    }
};
/*  substring的部分可以比對hash
 *  也可以使用rolling hash來比較prefix和subfix是否相等
 *  參考: 1392. Longest Happy Prefix
 *
 */
class Solution {
    int m = 1e9 + 7;
    int p = 31;
    int hasher(string& str) {
        int rtn{}, pk{1};
        for(auto& c : str) {
            rtn = (rtn + ((long long)c * pk) % m) % m;
            pk = (long long)pk * p % m;
        }
        return rtn;
    }
public:
    int countPrefixSuffixPairs(vector<string>& words) {
        unordered_map<int, int> mp; //rolling hash, count
        int ans{};
        for(int i = words.size() - 1; i >= 0; --i) {
            string& str = words[i];
            ans += mp[hasher(str)];
            long long hash1{}, hash2{};
            int pk{1}, sz = str.size();;
            for(int i = 0; i < sz; ++i) {
                hash1 = (hash1 + (long long)str[i] * pk % m) % m;
                hash2 = (hash2 * p % m + str[sz - i - 1]) % m;
                pk = (long long)pk * p % m;
                if(hash1 == hash2) {
                    mp[hash1]++;
                }
            }
        }
        return ans;
    }
};
