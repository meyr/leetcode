/* 參考解答
 *
 *
 */
class Solution {
public:
    int smallestRangeII(vector<int>& nums, int k) {
        int sz = nums.size();
        sort(begin(nums), end(nums));
        int ans = nums.back() - nums.front();
        for(int i = 0; i < sz - 1; ++i) {
            int high = max(nums.back() - k, nums[i] + k);
            int low = min(nums.front() + k, nums[i + 1] - k);
            ans = min(ans, high - low);
        }
        return ans;
    }
};
/*
    每個數字都有兩種可能 nums[i] - k, nums[i + k]
    一定是先排序

    when nums.size() = 1 --> special case --> ans = 0
    when nums.size() = 2 --> nums[i], nums[j]

                             nums[i] - k      nums[j] - k
                             nums[i] + k      nums[j] + k

                             nums[j] + k - (nums[i] - k) = nums[j] - nums[i] + 2 * k
                             nums[j] + k - (nums[i] + k) = nums[j] - nums[i]
                             nums[j] - k - (nums[i] - k) = nums[j] - nums[i]
                             nums[j] - k - (nums[i] + k) = nums[j] - nums[i] - 2 * k  (the best)

    when nums.size() = 3 --> a, b, c
                    a-k  b-k  c-k           當中間值b加入的時候，如果b-k, b+k不影響最大最小值
                    a+k  b+k  c+k           那結果就不會改變， 只有當加入的b-k有可能變成最小值
                                                                      或是b+k有可能變成最大值
                                                                      才會對結果造成影響

                   未加入b時the best answer是(c - k) - (a + k) 也就是說最小值會變大，最大值會變小
                                                               中間值有可能會變成最大值，或是最小值影響結果
                                                               因為每個值都必須+k/-k

                    每個值都嘗試+k/-k 等於 目前的值(idx)嘗試+k, 下一個值(idx+1)嘗試-k 等到idx++的時候
                                                                目前的值(idx+1)嘗試+k, 下一個值(idx+2)嘗試-k

                                                                對idx+1來說 +k/-k都嘗試過了。


                   a, b, c, d, e, f
                   +  +  +  +  +
                      -  -  -  -  -
*/
