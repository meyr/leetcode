/*  ref : https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/solutions/6172740/greedy-approach-by-kreakemp-vcby/
 *  
 *  Greedy point : 先取最小值 如果最小值被取過了就取下一個最小值
 *
 *  time  : O(NlogN + N) = O(NlogN)
 *  space : O(logN)
 */
class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        int ans{};
        sort(begin(nums), end(nums));
        for(int i = 0, last = INT_MIN; i < nums.size(); ++i) {  // last紀錄上一個取過的值
            int mn = nums[i] - k;
            int mx = nums[i] + k;
            if(last < mn) {             // 如果上一個取過的值 比nums[i] - k 還小 表示整段都可以取 則取最小
                last = mn;
                ans++;
            } else if(last < mx) {      // 上個取過的值還在 [nums[i] - k, nums[i] + k]範圍內，則取last下一個
                last = last + 1;
                ans++;
            }
        }
        return ans;
    }
};
