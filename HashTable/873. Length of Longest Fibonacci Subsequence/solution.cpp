/* 一直覺得這是DP的問題 但是寫不出來
 * 看了一下constraints 3 <= arr.length <= 1000 覺得可以先用暴力破解
 * 也就是訂好前兩個數字 再來看根據這兩個數字可以產生的最長subsequence
 *
 * time  : O(N^2)
 * space : O(N)
 *
 */
class Solution {
    unordered_map<int, int> m;
    int helper(vector<int>& arr, int i, int j) {
        int t = arr[i] + arr[j];
        if(m.count(t)) return helper(arr, j, m[t]) + 1;
        else return 0;
    }
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int ans{}, sz = arr.size();

        for(int i = 0; i < sz; ++i) // O(N)
            m[arr[i]] = i;

        for(int i = 0; i < sz; ++i) // O(N^2)
            for(int j = i + 1; j < sz; ++j)
                ans = max(ans, helper(arr, i, j) + 2);

        return ans < 3 ? 0 : ans;
    }
};
