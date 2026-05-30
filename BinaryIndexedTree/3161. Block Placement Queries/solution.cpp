/*  參考: https://leetcode.com/problems/block-placement-queries/solutions/5207345/going-backwards-fenwick-tree-by-votrubac-skdh/
 *  為什麼可以使用Binary index tree?
 *  因為取最大值 裡面的數值只會越來越大 不會有變小又變大的情況 就可以使用
 *  因為為了符合只會變大的情況 區間越變越大只有反過來尋找 所以必須反過來找queries
 *  
 *  time  : O(qlogM)
 */
class BIT{
    vector<int> bit;
    inline int lowbit(int x) { return x & (-x); }
public:
    BIT(int _sz) : bit(_sz + 1) {}
    void update(int idx, int val) {
        idx++;
        while(idx < bit.size()) {
            bit[idx] = max(bit[idx], val);  // 改成取最大值
            idx += lowbit(idx);
        }
    }
    int getMax(int idx) {
        idx++;
        int rtn{};
        while(idx > 0) {
            rtn = max(rtn, bit[idx]);   // 找到區間的最大值
            idx -= lowbit(idx);
        }
        return rtn;
    }
};

class Solution {
    enum status {type, pos, size};
    enum type {unknow, obs, blk};
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        set<int> blocks{0};
        for(const auto& q : queries)
            if(q[type] == obs)
                blocks.insert(q[pos]);
        BIT bit(5 * 1e5);
        // 建立BIT update(idx, sz) 表示idx以下的最大值是sz
        for(auto it = next(begin(blocks)); it != end(blocks); ++it)
            bit.update(*it, *it - *prev(it));
        vector<bool> rtn;
        for(int i = queries.size() - 1; i >= 0; --i) {
            int t = queries[i][type], x = queries[i][pos], sz = t == 1 ? 0 : queries[i][size];
            auto it = blocks.lower_bound(x);    // 找出比x小第一個obstacle
            if(t == obs) {
                if(next(it) != end(blocks))
                    bit.update(*next(it), *next(it) - *prev(it)); // __important__ 移除此obstacle前後區間加起來變成新的區間
                blocks.erase(it);
            } else // 有可能x到前面的obstacle就會符合 或是 x的前面有符合的區間
                rtn.push_back(x - *prev(it) >= sz || bit.getMax(x) >= sz);
        }
        reverse(begin(rtn), end(rtn));
        return rtn;
    }
};
