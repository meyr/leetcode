/* 使用left和right來表示cuts的上界和下界
 * 嘗試所有在left和right中間的切割
 *
 *  time  : O(N^2) , N : size of cuts
 *  space : O(N^2)
 */
class Solution {
    int helper(vector<int>& cuts, int left, int right) {
        if(~mem[left][right]) return mem[left][right];
        int rtn = 1e9;
        for(int i = left + 1; i < right; ++i) // 選擇left和right中間區域來切割
            rtn = min(rtn, helper(cuts, left, i) + helper(cuts, i, right));
        return mem[left][right] = rtn + cuts[right] - cuts[left];
    }
    vector<vector<int>> mem;
public:
    int minCost(int n, vector<int>& cuts) {
        cuts.push_back(0);              // __important__ 把0和n也推進去cuts當成上下邊界
        cuts.push_back(n);              // __important__
        sort(begin(cuts), end(cuts));
        
        int sz = cuts.size();
        mem.resize(sz, vector<int>(sz, -1));
        for(int i = 0; i < sz - 1; ++i)
            mem[i][i + 1] = 0;          // left + 1 == right 表示中間沒有可以切割
        
        return helper(cuts, 0, cuts.size() - 1);
    }
};
