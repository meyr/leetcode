/*
 *  標準的DP問題 因為從index往後看可以有最少的char來符合題目
 *
 *  time  : O(N^2)
 *  sapce : O(N)
 */
class Solution {
    unordered_map<char, unordered_set<string>> m; // 多使用char當索引可以減少time complexity
    int helper(string& s, int idx) {
        if(~mem[idx]) return mem[idx];
        int rtn = helper(s, idx + 1) + 1; // 不取 有三種狀況 1. 沒有符合的s[idx], 2, 沒有符合s[idx]開頭的dictionary 3, __故意不取__(不一定符合就要取)
        for(auto& d : m[s[idx]]) { // O(N)
            if(d.size() > s.size() - idx) continue;
            if(s.substr(idx, d.size()) == d)
                rtn = min(rtn, helper(s, idx + d.size()));
        }
        return mem[idx] = rtn;
    }
    vector<int> mem;
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        for(auto& d : dictionary) m[d[0]].insert(d);
        mem.resize(s.size() + 1, -1);
        mem.back() = 0;
        return helper(s, 0);
    }
};
