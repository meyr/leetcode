/*
    mid   1, 2, 3,   4, 5
    cnts  8, 8, [7], 7, 6
             >   <=  

    time  : O(NlogM) , M : maximum of nums, N : size of nums
    space : O(1)
*/
class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int left = 1, right = *max_element(begin(nums), end(nums));
        while(left < right) {
            int mid = left + (right - left) / 2;
            int cnt{};
            for(auto& n : nums) {
                if(n % mid == 0) cnt += n / mid - 1;
                else cnt += n / mid;
            }
            if(cnt <= maxOperations) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};
