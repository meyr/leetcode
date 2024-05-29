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
