/* 先使用top-down recursive 但是TLE
 *
 * time  : O(N)
 * space : O(N)
 *
 */
class Solution {
    enum player{alice, bob};
    int sz;
    long long helper(const vector<int>& stoneValue, int idx, int player) {
        if(idx >= sz) return 0;
        if(~mem[idx][player]) return mem[idx][player];
        if(player == alice) {
            return mem[idx][player] = max({
                helper(stoneValue, idx + 1, bob) + stoneValue[idx],
                helper(stoneValue, idx + 2, bob) + stoneValue[idx] + stoneValue[idx + 1],
                helper(stoneValue, idx + 3, bob) + stoneValue[idx] + stoneValue[idx + 1] + stoneValue[idx + 2],
            });
        } else {
            return mem[idx][player] = min({
                helper(stoneValue, idx + 1, alice) - stoneValue[idx],
                helper(stoneValue, idx + 2, alice) - stoneValue[idx] - stoneValue[idx + 1],
                helper(stoneValue, idx + 3, alice) - stoneValue[idx] - stoneValue[idx + 1] - stoneValue[idx + 2],
            });
        }
    }
    // f(idx, player) = f(idx, idx + 1, idx + 2, alice, bob)
    vector<vector<long long>> mem;
public:
    string stoneGameIII(vector<int>& stoneValue) {
        this->sz = stoneValue.size();
        stoneValue.push_back(0);
        stoneValue.push_back(0);
        mem.resize(sz, vector<long long>(2, -1));
        auto rtn = helper(stoneValue, 0, alice);
        if(rtn > 0) return "Alice";
        else if(rtn < 0) return "Bob";
        else return "Tie";
    }
};
/*
 * 修改成bottom-up tabulation
 *
 * time  : O(N)
 * space : O(N)
 */
class Solution {
    enum player{alice, bob};
    int sz;
public:
    string stoneGameIII(vector<int>& stoneValue) {
        this->sz = stoneValue.size();
        stoneValue.push_back(0);
        stoneValue.push_back(0);
        vector<vector<long long>> dp(sz + 3, vector<long long>(2));
        for(int i = sz - 1; i >= 0; --i) {
            for(int player = alice; player < 2; ++player) {
                if(player == bob) {
                    dp[i][player] = min({
                        dp[i + 1][!player] - stoneValue[i],
                        dp[i + 2][!player] - stoneValue[i] - stoneValue[i + 1],
                        dp[i + 3][!player] - stoneValue[i] - stoneValue[i + 1] - stoneValue[i + 2],
                    });
                } else {
                    dp[i][player] = max({
                        dp[i + 1][!player] + stoneValue[i],
                        dp[i + 2][!player] + stoneValue[i] + stoneValue[i + 1],
                        dp[i + 3][!player] + stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2],
                    });
                }
            }
        }
        if(dp[0][alice] > 0) return "Alice";
        else if(dp[0][alice] < 0) return "Bob";
        else return "Tie";
    }
};
