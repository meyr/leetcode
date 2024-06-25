/*
 *  推理參考 : https://leetcode.cn/problems/find-a-good-subset-of-the-matrix/solutions/2817195/zhao-dao-ju-zhen-zhong-de-hao-zi-ji-by-l-qldc/
 *
 *  k = 1, floor(1/2) = 0, 全部都為0
 *  k = 2, floor(2/2) = 1, 兩個row的column和最多為1, 表示成數值 row-n & row-m == 0
 *  k = 3, floor(3/2) = 1, 三個row的column和最多為1, 條件比k = 2還嚴格, 如果成立則一定可以找到 k == 2的狀況
 *  k = 4, floor(4/2) = 2, 如果不存在k = 1和k = 2的解, ...(看不懂)
 *
 *  所以只須找k = 1和k = 2的情況
 *  time  : O(NM), N = grid.size(), m = grid[0].size()
 *  space : O(N)
 */
class Solution {
public:
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid) {
        int sz = grid.size();
        unordered_map<int, int> m;
        for(int idx = 0; idx < sz; ++idx) {
            vector<int>& r = grid[idx];
            int v{};
            for(int i = 0; i < r.size(); ++i)
                v |= r[i] << i;
            if(v == 0) return {idx};
            for(auto& ref : m)
                if((ref.first & v) == 0) return {ref.second, idx};
            m[v] = idx;
        }
        return {};
    }
};
