/*  一開始使用以下的code結果TLE
 *  因為我在helper內使用了for loop 所以time complexity為O(K*N^2)
 */
class Solution {
    long long helper(const vector<int>& prices, int k, int idx) {
        if(idx == prices.size() || k == 0) return 0;
        else if(~mem[k][idx]) return mem[k][idx];
        long long rtn = helper(prices, k, idx + 1);
        for(int j = idx + 1; j < prices.size(); ++j)
            rtn = max(rtn, helper(prices, k - 1, j + 1) + abs(prices[idx] - prices[j]));
        return mem[k][idx] = rtn;
    }
    vector<vector<long long>> mem;
public:
    long long maximumProfit(vector<int>& prices, int k) {
        mem.resize(k + 1, vector<long long>(prices.size() + 1, -1));
        return helper(prices, k, 0);
    }
};
/*  為了避免上面狀況 只好把狀態拆出來
 *  
 *  time  : O(3KN) = O(KN)
 *  space : O(3KN) = O(KN)
 */
class Solution {
    using ll = long long;
    enum states{
        done,
        normal,
        selling,
        states_size
    };
    ll helper(const vector<int>& prices, int k, int idx, int type) {
        if(k == 0) return 0;
        else if(idx == prices.size() - 1) {                 // __important__ 最後一筆了 之前有交易的 必須強迫交易
            if(type == done) return 0;
            else if(type == normal) return prices[idx];
            else return -prices[idx];
        } else if(~mem[k][idx][type]) return mem[k][idx][type];
        else {
            ll rtn = helper(prices, k, idx + 1, type);                              // do nothing
            if(type == done) {                                                      // 之前已經完成交易 所以normal或是selling選一個
                rtn = max(rtn, helper(prices, k, idx + 1, normal)  - prices[idx]);
                rtn = max(rtn, helper(prices, k, idx + 1, selling) + prices[idx]);
            } else if(type == normal)                                               // 完成交易才把k - 1
                rtn = max(rtn, helper(prices, k - 1, idx + 1, done) + prices[idx]);
            else
                rtn = max(rtn, helper(prices, k - 1, idx + 1, done) - prices[idx]);
            return mem[k][idx][type] = rtn;
        }
    }
    vector<vector<vector<ll>>> mem;
public:
    long long maximumProfit(vector<int>& prices, int k) {
        int sz = prices.size();
        mem.resize(k + 1, vector<vector<ll>>(sz, vector<ll>(states_size, -1)));
        return helper(prices, k, 0, done);
    }
};
