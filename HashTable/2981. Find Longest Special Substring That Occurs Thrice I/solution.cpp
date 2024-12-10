/*
 *  使用unordered_map來統計每個special substring(都是同一個char)的數目
 *
 *  time  : O(N^2)
 *  space : O(N^2) 
 */
class Solution {
public:
    int maximumLength(string s) {
        unordered_map<string, int> m;
        int ans{-1};
        for(int i = 0; i < s.size(); ++i) {
            if(++m[s.substr(i, 1)] >= 3) ans = max(ans, 1);
            for(int j = i + 1; j < s.size() && s[j] == s[j - 1]; ++j)
                if(++m[s.substr(i, j - i + 1)] >= 3) 
                    ans = max(ans, j - i + 1);
        }
        return ans;
    }
};
/*
 *  同上 改使用2D vector取代unordered_map 可以不用使用substr()
 *
 */
class Solution {
public:
    int maximumLength(string s) {
        vector<vector<int>> cnt(26, vector<int>(s.size() + 1)); // 統計special substring的個數
        int ans{-1};
        for(int i = 0; i < s.size(); ++i) {
            if(++cnt[s[i] - 'a'][1] >= 3) ans = max(ans, 1);
            for(int j = i + 1; j < s.size() && s[j] == s[j - 1]; ++j)
                if(++cnt[s[i] - 'a'][j - i + 1] >= 3)
                    ans = max(ans, j - i + 1);
        }
        return ans;
    }
};
/*
 *   2024/12/10 daily challenge
 *
 *   只需要統計前三個長度
 *
 *   time  : O(N*3) = O(N)
 *   space : O(26 * N) = O(N)
 *
 */
class Solution {
public:
    int maximumLength(string s) {
        vector<vector<int>> mem(26, vector<int>(s.size() + 1));
        mem[s[0] - 'a'][1] = 1;
        int ans{-1};
        for(int i = 1, len = 1; i < s.size(); ++i) {
            len = s[i - 1] == s[i] ? len + 1 : 1;
            for(int j = len; j >= max(1, len - 2); --j) {
                if(++mem[s[i] - 'a'][j] >= 3)
                    ans = max(ans, j);
            }
        }
        return ans;
    }
};
