/*
 *   想了一陣子 後來看答案才發現是knapsack problem
 *   knapsack problem像是dynamic programming的brust force solution
 *
 *   怎麼辨識是這類的問題?
 *
 *   因為使用了memorization的技巧 所以time complexity為O(NM), N : coins size, M : amount
 *   如果O(NM) <= 10^6 就可以使用knapsack解法
 *   這一題的constrant, amount <= 5000, coins.length <= 300
 *   所以NM最大為5000 * 300 = 1500000 = 1.5 * 10^6
 */
class Solution {
    int helper(int amount, vector<int>& coins, int idx) {
        if(idx == coins.size()) return 0;
        else if(~mem[amount][idx]) return mem[amount][idx];

        int notake = helper(amount, coins, idx + 1);
        if(coins[idx] > amount) return mem[amount][idx] = notake;
        else {
            int take = helper(amount - coins[idx], coins, idx);
            return mem[amount][idx] = notake + take;
        }
    }
    vector<vector<int>> mem;
public:
    int change(int amount, vector<int>& coins) {
        mem.resize(amount + 1, vector<int>(coins.size(), -1));
        for(int i = 0; i < coins.size(); ++i) mem[0][i] = 1;
        return helper(amount, coins, 0);
    }
};
