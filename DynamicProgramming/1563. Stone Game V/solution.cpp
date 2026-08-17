/*  跟據題意 嘗試不同的分割 然後找出最大的score
 *
 *  time  : O(N^3)  因為N <= 500 
 *  space : O(N^2)
 */
class Solution {
    int helper(const vector<int>& pfs, int left, int right) {
        if(~mem[left][right]) return mem[left][right];
        int rtn{};
        for(int i = left, leftsum = 0, rightsum = 0; i <= right - 1; ++i) {
            leftsum = pfs[i] - pfs[left - 1];
            rightsum = pfs[right] - pfs[i];
            if(leftsum > rightsum) rtn = max(rtn, helper(pfs, i + 1, right) + rightsum);    // 選擇right
            else if(leftsum < rightsum) rtn = max(rtn, helper(pfs, left, i) + leftsum);     // 選擇left
            else rtn = max({                                                                // 兩邊都一樣就兩邊都試
                            rtn,
                            helper(pfs, i + 1, right) + rightsum,
                            helper(pfs, left, i) + leftsum
                        });
        }
        return mem[left][right] = rtn;
    }
    vector<vector<int>> mem;
public:
    int stoneGameV(vector<int>& stoneValue) {
        int sz = stoneValue.size();
        vector<int> pfs(sz + 1);
        mem.resize(sz + 1, vector<int>(sz + 1, -1));

        for(int i = 0; i <= sz; ++i)    // left == right game over
            mem[i][i] = 0;

        for(int i = 0; i < sz - 1; ++i) // left + 1 == right 只有兩個 所以只能分成left, right 所以選最小
            mem[i + 1][i + 2] = min(stoneValue[i], stoneValue[i + 1]);

        for(int i = 0; i < sz; ++i)     // 計算prefix sum避免重複計算
            pfs[i + 1] = pfs[i] + stoneValue[i];

        return helper(pfs, 1, sz);
    }
};
