/*  根據題意寫出的第一個solution結果TLE
 *
 *  重點是我在helper裡面用了一個for loop造成time complexity : O(BNK) , B : budget, N : sizeof items, K : budget/price
 *                                      如果price很小budget很大K就會很大 容易早成TLE
 *
 */
class Solution {
    enum pos{
        factor, price, free
    };
    int helper(const vector<vector<int>>& items , int budget, int idx) {
        if(idx == items.size()) return 0;
        if(budget < items[idx][price]) return mem[budget][idx] = 0;
        if(~mem[budget][idx]) return mem[budget][idx];
        int rtn = helper(items, budget, idx + 1);
        for(int i = 1; i * items[idx][price] <= budget; ++i)
            rtn = max(rtn, helper(items, budget - i * items[idx][price], idx + 1) + i + items[idx][free]);
        return mem[budget][idx] = rtn;
    }
    vector<vector<int>> mem;
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        sort(begin(items), end(items), [](auto& a, auto& b){
            return a[0] < b[0];
        });
        int sz = items.size();
        vector<int> copies(sz);
        for(int i = 0; i < sz; ++i) {
            if(i > 0 && items[i - 1][factor] == items[i][factor])
                copies[i] = copies[i - 1];
            else {
                for(int j = i + 1; j < sz; ++j)
                    if(items[j][0] % items[i][0] == 0)
                        copies[i]++;
            }
        }
        for(int i = 0; i < sz; ++i)
            items[i].push_back(copies[i]);
        sort(begin(items), end(items), [](auto& a, auto& b){
            return a[price] < b[price];
        });
        mem.resize(budget + 1, vector<int>(sz, -1));
        return helper(items, budget, 0);
    }
};
/*  根據AI的建議 移除for loop 但是多了一個狀態 bought 代表是否滿了這個item
 *  因為我們要知道是否是第一次購買
 *  這樣time complexity降成O(2BN) = O(BN)
 *
 *  但是這樣還是TLE
 */
class Solution {
    enum pos {
        factor, price, free
    };

    // mem[budget][idx][bought]
    // bought = 0: 還沒買過這個商品
    // bought = 1: 已經買過至少一個這個商品
    vector<vector<vector<int>>> mem;
    int helper(const vector<vector<int>>& items, int budget, int idx, int bought) {
        if (idx == items.size()) return 0;
        if (mem[budget][idx][bought] != -1) return mem[budget][idx][bought];
        int rtn = helper(items, budget, idx + 1, 0); // 不買了繼續往下一個item
        if (budget >= items[idx][price]) {
            if (bought == 0) {  // 第一次購買
                int buy_first = helper(items, budget - items[idx][price], idx, 1) + 1 + items[idx][free];
                rtn = max(rtn, buy_first);
            } else { // 不是第一次購買
                int buy_more = helper(items, budget - items[idx][price], idx, 1) + 1;
                rtn = max(rtn, buy_more);
            }
        }
        return mem[budget][idx][bought] = rtn;
    }

public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        sort(begin(items), end(items), [](const auto& a, const auto& b) {
            return a[0] < b[0];
        });
        int sz = items.size();
        vector<int> copies(sz, 0);
        for (int i = 0; i < sz; ++i) {
            if (i > 0 && items[i - 1][factor] == items[i][factor]) {
                copies[i] = copies[i - 1];
            } else {
                for (int j = 0; j < sz; ++j) {
                    if (i != j && items[j][0] % items[i][0] == 0) {
                        copies[i]++;
                    }
                }
            }
        }

        for (int i = 0; i < sz; ++i) {
            items[i].push_back(copies[i]);
        }

        mem.resize(budget + 1, vector<vector<int>>(sz, vector<int>(2, -1)));
        return helper(items, budget, 0, 0);
    }
};
/*  再要求AI不要修改top-down架構有辦法加速嗎?
 *  1. 資料結構扁平化 : 使用一維array取代三維items 大幅提升快取命中率。
 *  2. 將 vector 改為「原生靜態陣列」, 原本的mem是三維vector改為三維array
 *  3. 剪枝優化（Pruning）：跳過不可能的狀態, 紀錄每個index後面最小的price 不要每個都嘗試
 */
int mem[5005][1005][2];
int prices[1005];
int frees[1005];
int min_remain_price[1005]; // 用於剪枝：記錄從 idx 開始往後最便宜的商品價格
int total_items = 0;

class Solution {
    enum pos { factor, price, free };

    int helper(int budget, int idx, int bought) {
        if (idx == total_items) return 0;
        if (budget < min_remain_price[idx]) return 0;
        if (mem[budget][idx][bought] != -1) return mem[budget][idx][bought];
        int rtn = helper(budget, idx + 1, 0);
        int p = prices[idx];
        if (budget >= p) {
            if (bought == 0) {
                int buy_first = helper(budget - p, idx, 1) + 1 + frees[idx];
                if (buy_first > rtn) rtn = buy_first;
            } else {
                int buy_more = helper(budget - p, idx, 1) + 1;
                if (buy_more > rtn) rtn = buy_more;
            }
        }

        return mem[budget][idx][bought] = rtn;
    }

public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        // 關閉 C++ I/O 同步加速
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        sort(begin(items), end(items), [](const auto& a, const auto& b) {
            return a[0] < b[0];
        });

        int sz = items.size();
        total_items = sz;
        vector<int> copies(sz, 0);

        for (int i = 0; i < sz; ++i) {
            prices[i] = items[i][price];
            if (i > 0 && items[i - 1][factor] == items[i][factor]) {
                copies[i] = copies[i - 1];
            } else {
                for (int j = 0; j < sz; ++j) {
                    if (i != j && items[j][0] % items[i][0] == 0) {
                        copies[i]++;
                    }
                }
            }
            frees[i] = copies[i];
        }

        // 【核心剪枝預處理】後綴最小值：計算從 idx 到最後，最便宜的商品價格是多少
        int cur_min = 1e9;
        for (int i = sz - 1; i >= 0; --i) {
            cur_min = min(cur_min, prices[i]);
            min_remain_price[i] = cur_min;
        }

        memset(mem, -1, sizeof(mem));
        return helper(budget, 0, 0);
    }
};
