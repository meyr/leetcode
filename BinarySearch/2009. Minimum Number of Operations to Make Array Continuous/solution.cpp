/*
 *   參考解答
 *
 *   一開始是想用nums[i] 當成中心點 向前向後找
 *   不過這樣會有漏洞 nums[i]不一定是中心點
 *
 *   但是一定會有一個nums[i]是可以當成起點
 *
 *   time  : O(NlogN)
 *   space : O(logN)
 */

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int sz = nums.size(), ans = sz;
        sort(begin(nums), end(nums)); // O(NlogN)
        // 把不重複的放到vector前面 並得到last index
        int last = unique(begin(nums), end(nums)) - begin(nums); 
        for(int left = 0; left < last; ++left) { // 把nums[i]當成起點，用binary search找終點nums[i] + sz - 1
            int right = upper_bound(begin(nums), begin(nums) + last, nums[left] + sz - 1) - nums.begin();
            ans = min(ans, sz - (right - left));
        }
        return ans;
    }
};
