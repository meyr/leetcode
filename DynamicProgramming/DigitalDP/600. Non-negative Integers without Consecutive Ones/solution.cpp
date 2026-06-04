/*
 *  紀錄上一個選了哪個binary 這樣才可以避免連續1的出現
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    int helper(string_view str, int idx, int prev, bool is_tight) {
        if(idx == str.size()) return 1;
        if(!is_tight && ~mem[idx][prev][is_tight]) return mem[idx][prev][is_tight];
        int limit = is_tight ? str[idx] - '0' : 1;
        int ans{};
        for(int d = 0; d <= limit; ++d) {
            if(d == 0 || (d == 1 && prev == 0))                         // __important__ 這次選了0不用管prev, 這次選了1必須確定prev == 0
                ans += helper(str, idx + 1, d, is_tight && d == limit);
        }
        return mem[idx][prev][is_tight] = ans;
    }
    string getBinaryString(int n) {
        string rtn;
        while(n) {
            rtn += (n % 2 + '0');
            n >>= 1;
        }
        reverse(begin(rtn), end(rtn));
        return rtn;
    }
    vector<vector<vector<int>>> mem;
public:
    int findIntegers(int n) {
        string str = getBinaryString(n);
        mem.resize(str.size() + 1, vector<vector<int>>(2, vector<int>(2, -1)));
        return helper(getBinaryString(n), 0, 0, true);
    }
};
