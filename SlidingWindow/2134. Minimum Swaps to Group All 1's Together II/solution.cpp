/*
 * 把解答所以可寧的位置都走過一次 就可以知道最小的swap
 *
    0, 1, 0, 1, 1, 0, 0
    1, 1, 1
       1, 1, 1
          1, 1, 1
             1, 1, 1
                1, 1, 1
    1              1, 1, 
    1, 1              1
*
*   
*   time  : O(N)
*   space : O(1)
*/
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int cnt{};
        for(auto& n : nums) cnt += n == 1;
        if(cnt == 0 || cnt == 1) return 0;
        int ans = nums.size(), onecnt{};
        for(int i = 0; i < nums.size() + cnt - 1; i++) {
            onecnt += nums[i % nums.size()] == 1;
            onecnt -= i >= cnt ? nums[(i - cnt + nums.size()) % nums.size()] == 1 : 0;   
            ans = min(ans, cnt - onecnt);
        }
        return ans;
    }
};

