/*  每次都把新的map<char, int>統計所有char出現頻率傳入helper
 *  並且統計個數 ==> TLE
 *
 */
class Solution {
    int mod = 1e9 + 7;
    void print(map<char, int>& m) {
        for(auto& ref : m)
            cout << "(" << ref.first << "," << ref.second << ")";
        cout << endl;
    }
    string genKey(map<char, int>& m, int t) {
        string rtn;
        rtn += to_string(t);
        for(auto& ref : m)
            rtn += ref.first + to_string(ref.second);
        return rtn;
    }
    int helper(map<char, int>& m, int t) {
        int ans{};
        //print(m);
        if(m.rbegin()->first + t > 'z') {       // 檢查最後一個char是否經過t轉換後超過'z'
            char lastc = m.rbegin()->first;
            int move = 'z' - lastc + 1;
            string key = genKey(m, move);
            if(mem.count(key)) return mem[key];
            map<char, int> _m;                  // 產生新的map來統計char的出現頻率
            _m['a'] = m.rbegin()->second;
            _m['b'] = m.rbegin()->second;
            for(auto it = m.begin(); it != prev(m.end()); ++it) {
                char nxtc = it->first + move;
                _m[nxtc] = (_m[nxtc] + it->second) % mod;
            }
            mem[key] = ans = (ans + helper(_m, t - move)) % mod;
        } else {
            for(auto& ref : m)
                ans = (ans + ref.second) % mod;
        }
        return ans;
    }
    unordered_map<string, int> mem;
public:
    int lengthAfterTransformations(string s, int t) {
        map<char, int> m;
        for(auto& c : s) m[c]++;
        return helper(m, t);
    }
};
/*  參考 : https://leetcode.com/problems/total-characters-in-string-after-transformations-i/solutions/5972920/string-evolution-the-transformation-chal-2csj/
 *  想法類似改用vector<int>來記錄char出現頻率 這樣就可以AC
 *
 */
class Solution {
public:
    int lengthAfterTransformations(string s, int t) {
        const int MOD = 1e9 + 7;
        vector<int> cnt(26, 0);
        for (char c : s) 
            cnt[c - 'a']++;

        for (int j = 0; j < t; j++) {
            vector<int> tmp(26, 0);
            for (int i = 0; i < 26; i++) {
                if (i == 25) {                          // 因為'z'下一次轉換會變成"ab"
                    tmp[0] = (tmp[0] + cnt[i]) % MOD;
                    tmp[1] = (tmp[1] + cnt[i]) % MOD;
                } else
                    tmp[i + 1] = (tmp[i + 1] + cnt[i]) % MOD;
            }
            cnt = move(tmp);
        }
        return accumulate(begin(cnt), end(cnt), 0LL) % MOD;
    }
};
/*  參考 : https://leetcode.com/problems/total-characters-in-string-after-transformations-i/solutions/5973021/javacpython-dp-by-lee215-soqq/
 *  考慮只有一個char他的變化就是dp
 *  把string拆成一個一個char 相加起來就是答案
 */
class Solution {
    int mod = 1e9 + 7;
    int dp[100100] = {0};
public:
    Solution() {
        for(int i = 0; i < 26; ++i)
            dp[i] = 1;
        for(int i = 26; i < 100100; ++i)                    // __important__ 因為變成兩個char的相加    z->ab, ...yz->zab-> abbc       dp[25] = 1, dp[26] = dp[0] + dp[1] = 2, dp[27] = dp[1] + dp[2]   
            dp[i] = (dp[i - 26] + dp[i - 26 + 1]) % mod;    //                                        25  26     50   51     52       dp[51] = dp[25] + dp[26] = dp[25] + dp[0] + dp[1] = 3
    }                                                       //                                                                        dp[52] = dp[26] + dp[27] = dp[0] + dp[1] + dp[1] + dp[2] = 4
    int lengthAfterTransformations(string s, int t) {
        int res{};
        for(auto& c : s)
            res = (res + dp[c - 'a' + t]) % mod;
        return res;
    }
};
