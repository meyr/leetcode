/*
 *      題目提到可以刪除prefix和suffix但是最後不能是empty
 *      其實就是任一個subarray的意思 也就是所以可能的subarray的相乘 mod k之後的數量
 *
 *      參考gemini給的top-down recirsive解答
 *
 *      time  : O(K*N^2)
 *      space : O(N)
 */
class Solution {
public:
    int k;
    vector<long long> solve(const vector<int>& nums, int i) {
        vector<long long> res(k, 0);
        int numMod = nums[i] % k;
        res[numMod] = 1;
        if(mem[i][0] != -1) return mem[i];                  // 只要檢查第一個element是否為-1即可
        if (i > 0) {
            vector<long long> prevRes = solve(nums, i - 1);
            for (int r = 0; r < k; ++r) {
                int newMod = (r * numMod) % k;
                res[newMod] += prevRes[r];
            }
        }
        return mem[i] = res;
    }
    vector<vector<long long>> mem;
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> ans(k, 0);
        mem.resize(n, vector<long long>(k, -1));        // memorization 是把每個index的vector<long long>都記錄下來
        this->k = k;
        for (int i = 0; i < n; ++i) {                   // 為什麼每個index都要跑過一次?
            vector<long long> res = solve(nums, i);     // 因為solve是對以i為結尾的subarray進行統計
            for (int r = 0; r < k; ++r)                 // 在solve function內一定會使用到nums[i] 所以就是以nums[i]為結尾的subarray
                ans[r] += res[r];
        }

        return ans;
    }
};
