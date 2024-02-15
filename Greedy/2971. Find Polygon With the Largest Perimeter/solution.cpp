// 2024.02.15 daily challenge
// 先排序，然後檢查是否有符合條件的polygon

class Solution
{
public:
    long long largestPerimeter(vector<int>& nums)
    {
        sort(begin(nums), end(nums)); // O(NlogN)
        long long ans{ -1}, cur = nums[0] + nums[1];
        for (int i = 2; i < nums.size(); ++i) { // O(N)
            if (nums[i] < cur)
                ans = max(ans, cur + nums[i]);
            cur += nums[i];
        }
        return ans;

        // time  : O(NlogN + N) = O(NlogN)
        // space : O(logN)
    }
};
