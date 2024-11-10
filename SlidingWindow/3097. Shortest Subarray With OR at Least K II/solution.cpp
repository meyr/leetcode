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
/*  2024/11/10 daily challenge
 *  想法和上面一樣使用slinding window和bit manipulation來解題
 *  但是改用bitset來做可以比較精簡而且比較不會有bug
 */
 class Solution {
    vector<int> cnt(32);
    void check(bitset<32>& xorval, bitset<32> val, int op) {
        for(int i = 0; i < 32; ++i) {
            if(val.test(i)) {
                cnt[i] += op;
                xorval.set(i, cnt[i] > 0);
            }
        }
    }
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        if(k == 0) return 1; // special case
        bitset<32> xorval;
        int sz = nums.size(), ans = sz + 1;
        for(int left = 0, right = 0; right < sz; ++right) {
            check(xorval, nums[right], 1);
            while(left <= right && xorval.to_ulong() >= k) {
                ans = min(ans, right - left + 1);
                check(xorval, nums[left++], -1);
            }
        }
        return ans > sz ? -1 : ans;
    }
};
