/* 
 * 因為是mountain array 一開始的想法是找出左右邊比自己小的最長
 * 所以建立 fwd和bwd去看 而且長度只有nums.size() <= 1000 
 * 所以使用O(N^2) 應該也可以通過
 *
 *  2, 1, 1, 5, 6, 2, 3, 1   sz = 8
 *
 *  0, 0, 0, 1, 2, 1, 2, 0  backward
 *  1, 0, 0, 2, 2, 1, 1, 0  fordward
 *
 *  2, 1, 1, 4, 5, 3, 4, 0
 *              *
 *
 * time  : O(N^2 + N^2) = O(N^2)
 * space : O(N)
 */
class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int sz = nums.size();
        int ans = sz;
        vector<int> bwd(sz), fwd(sz);
        for(int i = 0; i < sz; ++i) {
            for(int j = 0; j < i; ++j) {
                if(nums[j] < nums[i])
                    bwd[i] = max(bwd[i], bwd[j] + 1);
            }
        }

        for(int i = sz - 1; i >= 0; --i) {
            for(int j = sz - 1; j > i; --j) {
                if(nums[j] < nums[i]) {
                    fwd[i] = max(fwd[i], fwd[j] + 1);
                }
            }
            if(fwd[i]  && bwd[i]) // __important__ 左右都有element才是mountain array
                ans = min(ans, sz - fwd[i] - bwd[i] - 1);
        }

        return ans;
    }
};
/* 參考解答 主要是找出LIS(longest increase subsequence)
 *          左右邊各找一次 結合起來就是最長的mountain array
 *
 * time  : O(NlogN)
 * space : O(N)
 */
class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int sz = nums.size(), ans = sz;
        vector<int> left(sz), right(sz), v;
        for (int i = 0 ; i < sz; ++i) {
            auto it = lower_bound(begin(v), end(v), nums[i]);
            left[i] = it - begin(v);
            if (it != end(v)) *it = nums[i];
            else v.push_back(nums[i]);
        }
        v.clear();
        for (int i = sz - 1; i >= 0; --i) {
            auto it = lower_bound(begin(v), end(v), nums[i]) ;
            right[i] = it - begin(v);
            if (it != end(v)) *it = nums[i];
            else v.push_back(nums[i]);
            if(left[i] && right[i])
                ans = min(ans, sz - left[i] - right[i] - 1);
        }

        return ans;
    }
};
