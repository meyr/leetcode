/*  我寫出來的解答TLE
 */
 class Solution {
    bool helper(vector<int>& ans, int val) {
        if(val == 1) {
            rtn = max(rtn, ans);    // 表示收集所有的可能--> TLE
            return true;
        } else {
            for(int i = 0; i + val < ans.size(); ++i) {
                if(!ans[i] && !ans[i + val]) {
                    ans[i] = ans[i + val] = val;
                    //if(helper(ans, val - 1)) return true;
                    helper(ans, val - 1);
                    ans[i] = ans[i + val] = 0;
                }
            }
            return false;
        }
    }
    vector<int> rtn;
public:
    vector<int> constructDistancedSequence(int n) {
        rtn.resize(2 * n - 1);
        vector<int> ans(2 * n - 1);
        helper(ans, n);
        for(int i = 0; i < rtn.size(); ++i)
            if(!rtn[i]) {
                rtn[i] = 1;
                break;
            }
        return rtn;
    }
};
/*  參考解答: https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/solutions/1009498/c-greedy-search-by-votrubac-mo9p/
 *  類似的想法
 *  Greedy point : 因為要找出Lexicographically Largest Valid Sequence
 *                 所以從最大的數字開始放入，當全部都放入p == arr.size()就表示找到解答
 *
 */
class Solution {
public:
    bool dfs(vector<int> &taked, vector<int> &arr, int p) {    
        if (p == arr.size()) return true;
        else if (arr[p] != 0) return dfs(taked, arr, p + 1);
        else {
            for (int i = taked.size() - 1; i >= 1; --i) {
                int dist = i == 1 ? 0 : i; // 只有i == 1取1個，也就是自己。其他取兩個
                if (!taked[i] && dist + p < arr.size() && arr[dist + p] == 0) { // 沒有用過數字，且空格滿足條件就試試看。
                    arr[p] = arr[p + dist] = i;
                    taked[i] = 1;
                    if(dfs(taked, arr, p + 1)) return true;
                    taked[i] = 0;
                    arr[p] = arr[p + dist] = 0;
                }
            }
            return false;
        }
    }
    vector<int> constructDistancedSequence(int n) {
        vector<int> arr((n - 1) * 2 + 1), taked(n + 1);
        dfs(taked, arr, 0);
        return arr;     
    }
};
