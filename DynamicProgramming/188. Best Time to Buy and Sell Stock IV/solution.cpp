class Solution {
    enum status{
        buy, sell, status_size
    };
    int helper(int k, const vector<int>& prices, int idx, int prev) {
        if(k == 0 || prices.size() == idx) return 0;
        else if(~mem[k][idx][prev]) return mem[k][idx][prev];

        int donothing = helper(k, prices, idx + 1, prev);

        int dotrans{};
        if(prev == sell)
            dotrans = helper(k, prices, idx + 1, buy) - prices[idx];
        else
            dotrans = helper(k - 1, prices, idx + 1, sell) + prices[idx];

        return mem[k][idx][prev] = max(donothing, dotrans);
    }
    vector<vector<vector<int>>> mem;
public:
    int maxProfit(int k, vector<int>& prices) {
        mem.resize(k + 1, vector<vector<int>>(prices.size() + 1, vector<int>(status_size, -1)));
        return helper(k, prices, 0, sell);
    }
};
