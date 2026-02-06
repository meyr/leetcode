/*
 * balanced array的定義是 max <= min * k
 * 所以使用slinding window只要這條件不符合 就縮小window
 * 並且記錄最大的window長度
 *
 * time  : O(NlogN + N) = O(N)
 * space : O(logN)
 *
 */
class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));
        int maxlen{};
        for(int left = 0, right = 0; right < nums.size(); ++right) {
            while(left < right && (long long)nums[left] * k < nums[right])
                left++;
            maxlen = max(maxlen, right - left + 1);
        }
        return nums.size() - maxlen;
    }
};
