/*  題目看不太懂問了一下gemini
 *  就是每個index i只能往前往後跳[i-d, i+d]且不能超過arr的範圍
 *  也不能跳超過比自己還高的物體 也就是即使比自己高的物體後面有比自己低的也不行 <-- 這是重點
 *  所以遇到比自己高的就break跳出迴圈
 *
 *  time  : O(ND)
 *  space : O(N)
 */
class Solution {
    int helper(const vector<int>& arr, int idx, int d) {
        int rtn{};
        if(~mem[idx]) return mem[idx];
        for(int j = 1; j <= d; ++j) {
            if(idx + j < arr.size() && arr[idx + j] < arr[idx])
                rtn = max(rtn, helper(arr, idx + j, d) + 1);
            else break;
        }
        for(int j = 1; j <= d; ++j) {
            if(idx - j >= 0 && arr[idx - j] < arr[idx])
                rtn = max(rtn, helper(arr, idx - j, d) + 1);
            else break;
        }
        return mem[idx] = rtn;
    }
    vector<int> mem;
public:
    int maxJumps(vector<int>& arr, int d) {
        int ans{};
        mem.resize(arr.size(), -1);
        for(int i = 0; i < arr.size(); ++i)
            ans = max(ans, helper(arr, i, d) + 1);
        return ans;
    }
};
