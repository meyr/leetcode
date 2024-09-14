/*
    想法是先統計每個idx的1的個數 cnt[idx][i]

    1 --> 01   01 --| 23
    0 --> 00   01   |     --| 22
    2 --> 10   11   |       |     --| 22
    1 --> 01   12   |       |       |     --| 12
    3 --> 11   23 --|     --|     --|     --|
*/
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int sz = nums.size();
        vector<vector<int>> cnt(32, vector<int>(sz + 1));
        for(int i = 0; i < sz; ++i) {
            int m = nums[i];
            for(int idx = 0; idx < 32; ++idx) {
                if(i == 0) cnt[idx][i + 1] = (m & 1);
                else cnt[idx][i + 1] = cnt[idx][i] + (m & 1);
                m >>= 1;
            }
        }
        vector<int> ans;
        for(int i = 0; i < sz - 1; ++i) {
            int j{i + 1};
            for(int idx = 0; idx < 32; ++idx) {
                if(cnt[idx][sz] - cnt[idx][i]) {
                    j = max(j, 
                        (int)(upper_bound(begin(cnt[idx]) + i, 
                                     end(cnt[idx]), 
                                     cnt[idx][i]) - 
                                     begin(cnt[idx])));
                }
            }
            ans.push_back(j - i);
        }
        ans.push_back(1);
        return ans;
    }
};
/*
 *  lee215大神簡單的解答
 */
vector<int> smallestSubarrays(vector<int>& A) {
    int last[30] = {}, n = A.size();
    vector<int> res(n, 1);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < 30; ++j) {
            if (A[i] & (1 << j))
                last[j] = i;
            // last[j] 從i往後面看第j個bit是1
            // 因為subarray包誇自己 如果第j個bit是1則使用自己的
            //                     如果第j個bit是0則使用最近的num
            res[i] = max(res[i], last[j] - i + 1);
        }
    }
    return res;
}
