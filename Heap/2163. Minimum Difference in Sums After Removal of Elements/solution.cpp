/*  參考題目hint
 *  一個vector<int> nums, 需要刪除 sz / 3 個element使得前 sz/3個element和 減掉 後 sz/3個element的和為最小
 *  假設數值為 a, b, c, d, e, f  -- 刪除掉兩個 --> a, c, e, f  則sum(a+c) - sum(e+f)為最小
 *  從結果來看   a, c, e, f 就是在index i = c 的地方往前看 選n個數值和為最小(包刮自己)
 *                                                  往後看 選n個數值和為最大(不包刮自己)
 *  所以使用priority_queue來把最大和最小值剔除掉 
 *  
 *  time  : O(NlogN + NlogN + N) = O(NlogN)
 *  space : O(N)
 */
class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        int sz = nums.size();
        int n = sz / 3;
        priority_queue<int> maxheap;
        vector<long long> minSum(sz); // including self
        long long sum{};
        for(int i = 0; i < sz; ++i) {
            sum += nums[i];
            maxheap.push(nums[i]);
            if(maxheap.size() > n) {
                sum -= maxheap.top();
                maxheap.pop();
            }
            minSum[i] = sum;
        }
        sum = 0;
        priority_queue<int, vector<int>, greater<>> minheap;
        vector<long long> maxSum(sz);
        for(int i = sz - 1; i >= 0; --i) {
            if(minheap.size() > n) {
                sum -= minheap.top();
                minheap.pop();
            }
            maxSum[i] = sum;
            minheap.push(nums[i]);
            sum += nums[i];

        }
        long long ans = LLONG_MAX;
        for(int i = n - 1; i < sz - n; ++i)
            ans = min(ans, minSum[i] - maxSum[i]);
        return ans;
    }
};
