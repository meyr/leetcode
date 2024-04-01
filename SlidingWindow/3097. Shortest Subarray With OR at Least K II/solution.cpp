/*
 *  使用vector<int> cnt來統計每個 1 << i 的set bit 有多少個
 *  time  : O(N)
 *  space : O(1)
 */

class Solution {
    vector<int> cnt;
    void addNum(int& cur, int num) {
        for(int i = 0; i < 32; ++i) {
            if((num >> i) & 1) {
                if(cnt[i]++ == 0) cur |= 1 << i;
            }
        }
    }
    void subNum(int& cur, int num) {
        for(int i = 0; i < 32; ++i) {
            if((num >> i) & 1) {
                if(--cnt[i] == 0) cur &= ~(1 << i);
            }
        }
    }
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int sz = nums.size();
        int ans = sz + 1;
        int cur{};
        cnt.resize(32);
        for(int l = 0, r = 0; r < sz; ++r) {
            addNum(cur, nums[r]);
            while(l <= r && cur >= k) {
                ans = min(ans, r - l + 1);
                subNum(cur, nums[l++]);
            }
        }
        return ans == sz + 1 ? -1 : ans;
    }
};
