/*
 *      本來以為是DP問題 結果MLE 因為 nums.size() <= 1e5
 *      因為使用DP需要O(X * N^2)
 */
class Solution {
    int sz;
    int helper(const vector<int>& nums, int left, int right, int x) {
        if(x == 0) return 0;
        else if(left > right) return sz + 1;
        else if(~mem[left][right][x]) return mem[left][right][x];
        else {
            int rtn{sz + 1};
            if(nums[left] <= x) rtn = min(rtn, helper(nums, left + 1, right, x - nums[left]) + 1);
            if(nums[right] <= x) rtn = min(rtn, helper(nums, left, right - 1, x - nums[right]) + 1);
            return mem[left][right][x] = rtn;
        }
    }
    using vi = vector<int>;
    using vvi = vector<vi>;
    using vvvi = vector<vvi>;
    vvvi mem;
public:
    int minOperations(vector<int>& nums, int x) {
        this->sz = nums.size();
        auto total = accumulate(begin(nums), end(nums), 0);
        if(total == x) return sz;
        else if(total < x) return -1;
        else {
            mem.resize(sz, vvi(sz, vi(x + 1, -1)));
            auto rtn = helper(nums, 0, sz - 1, x);
            return rtn > sz ? -1 : rtn;
        }
    }
};
/*
 *      因為只取左右兩邊 所以等於是找出一個最大的window其中的sum == total - x
 *
 *
 *      time  : O(N)
 *      sapce : O(1)
 */
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        auto total = accumulate(begin(nums), end(nums), 0);
        if(total < x) return -1;
        else if(total == x) return nums.size();
        else {
            int target = total - x;
            unordered_map<int, int> ump;
            ump[0] = -1;
            int ans{};
            for(int i = 0, sum = 0; i < nums.size(); ++i) {
                sum += nums[i];
                if(ump.count(sum - target))
                    ans = max(ans, i - ump[sum - target]);
                if(!ump.count(sum))
                    ump[sum] = i;
            }
            if(ans > 0) return nums.size() - ans;
            else return -1;
        }
    }
};
/*
 *      也可以使用slinding window找出最長的windows和為target = total - x
 *
 *      time  : O(N)
 *      space : O(1)
 */
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        auto total = accumulate(begin(nums), end(nums), 0);
        auto target = total - x;
        if(target == 0) return nums.size();
        else if(target < 0) return -1;
        int maxLen{};
        for(int left = 0, right = 0, sum = 0; right < nums.size(); ++right) {
            sum += nums[right];
            while(left < right && sum > target)
                sum -= nums[left++];
            if(sum == target)
                maxLen = max(maxLen, right - left + 1);
        }
        return maxLen == 0 ? -1 : nums.size() - maxLen;
    }
};
