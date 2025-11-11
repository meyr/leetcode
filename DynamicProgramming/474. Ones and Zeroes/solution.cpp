/*
 *  time  : O(MNL), L : length of strs
 *  space : O(MNL) 
 */
class Solution {
    int helper(int m, int n, int idx) {
        int ans{};
        if(idx == vpii.size()) ans = 0;
        else if(~mem[m][n][idx]) return mem[m][n][idx];
        else {
            ans = helper(m, n, idx + 1);
            pair<int, int>& pii = vpii[idx];
            if(m >= pii.first && n >= pii.second)
                ans = max(ans, helper(m - pii.first, n - pii.second, idx + 1) + 1);
        }
        return mem[m][n][idx] = ans;
    }
    vector<pair<int, int>> vpii;
    vector<vector<vector<int>>> mem;
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        mem.resize(m + 1, vector<vector<int>>(n + 1, vector<int>(strs.size() + 1, -1)));
        for(auto& str : strs) {
            int zcnt{}, ocnt{};
            for(auto& c : str) {
                zcnt += c == '0';
                ocnt += c == '1';
            }
            vpii.push_back({zcnt, ocnt});
        }
        return helper(m, n, 0);
    }
};
