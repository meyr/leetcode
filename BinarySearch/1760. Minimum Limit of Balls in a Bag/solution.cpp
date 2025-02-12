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
/* 2025/02/12 daily challenge
 *  maximum minimize problem --> binary search
 *
 *   penalty : 1, 2, 3, 4, 5, 6, 7
 *   ops     : 8, 7, 6, 6, [5], 5, 4
 *                      >   <=
 *
 *   9 -> 1, 8 -> 1, 1, 7 -> 1, 1, 1, 6 -> 1, 1, 1, 1, 5 -> 1, 1, 1, 1, 1, 4 -> 1, 1, 1, 1, 1, 1, 3 -> 1, 1, 1, 1, 1, 1, 1, 2 -> 1, 1, 1, 1, 1, 1, 1, 1, 1
 *   9 -> 2, 7 -> 2, 2, 5 -> 2, 2, 2, 3 -> 2, 2, 2, 2, 1
 *   9 -> 3, 6 -> 3, 3, 3
 *   9 -> 4, 5 -> 4, 4, 1
 *   9 -> 5, 4
 *   9 -> 6, 3
 *   9 -> 7, 2
 *   9 -> 8, 1
 *   9 -> 
 *
 *   time  : O(N + NlogM) = O(NlogM), N : sizeof nums, M : maximum num in nums
 *   space : O(1)
 */
class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int left = 1, right = *max_element(begin(nums), end(nums));
        while(left < right) {
            int mid = left + (right - left) / 2;
            int cnt{};
            for(auto&　n : nums)
                    cnt += n / mid - !(n % mid);
            if(cnt <= maxOperations) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};
