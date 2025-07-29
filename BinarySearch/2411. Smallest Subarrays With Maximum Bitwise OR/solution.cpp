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
/*  2025/07/29 daily challenge
 *  根據題意 一開始寫出了TLE解答
 *
 *  time  : O(N^2)
 */
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int sz = nums.size();
        vector<int> maxor(sz);
        maxor[sz - 1] = nums[sz - 1];
        for(int i = sz - 2; i >= 0; --i)
            maxor[i] = maxor[i + 1] | nums[i];
        vector<int> ans;
        for(int i = 0; i < sz; ++i) {
            int target = maxor[i];
            int cur{};
            for(int j = i; j < sz; ++j) {
                cur |= nums[j];
                if(cur == target) {
                    ans.push_back(j - i + 1);
                    break;
                }
            }
        }
        return ans;
    }
};
/*  根據hint其實我們只在乎 maxor的setbit最早出現的index
 *  所以改寫成下面
 *
 *  time  : O(32N) = O(N)
 *  space : O(N+32) = O(N)
 */
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int sz = nums.size();
        int maxor{};
        vector<int> rtn(sz), prev(32, sz);
        for(int i = sz - 1; i >= 0; --i) {
            maxor |= nums[i];               // 統計目前的maximum xor value
            int ans{};
            if(maxor == 0) ans = 1;         // 如果是0 就不需要計算
            else{
                for(int j = 0; j < 32; ++j) {
                    if(nums[i] & (1 << j))      // update setbit位置
                        prev[j] = i;
                    if(maxor & (1 << j))
                        ans = max(ans, prev[j] - i + 1);
                }
            }
            rtn[i] = ans;
        }
        return rtn;
    }
};
/*  參考: https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/solutions/2588015/javacpython-bit-solution-with-explanatio-r6hi/
 *
 *  想法和上面一樣 
 *  不需要maxor 因為last[i] 有值(>0) 就表示了maxor的setbit
 *  另外 last[30] = {}, 且res[i] = max(res[i], last[j] - i + 1) 是取max, 所以當last[j] == 0 為負值不會取
 *
 *  time  : O(30N) = O(N)
 *  space : O(N + 30) = O(N)
 */
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& A) {
        int last[30] = {}, n = A.size();
        vector<int> res(n, 1);
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < 30; ++j) {
                if (A[i] & (1 << j))
                    last[j] = i;
                res[i] = max(res[i], last[j] - i + 1);
            }
        }
        return res;
    }
};
