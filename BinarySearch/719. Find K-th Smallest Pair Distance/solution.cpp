/*
 *  一開始本來想用priority_queue但是怎麼想都不對
 *  後來看Topics有binary search才寫出以下解答
 *
 *  time  : O(NlogNlogM) , N : size of nums, M : maximum different of nums(nums.back() - nums.front())
 *  space : O(logN), sorting algorithm 
 */
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(begin(nums), end(nums)); // 先排序
        int left = 0, right = nums.back() - nums.front();
        while(left < right) {
            int mid = left + (right - left) / 2;
            int cnt{};
            for(int i = 0; i < nums.size(); ++i) { //O(NlogN)
                cnt += upper_bound(begin(nums), end(nums), nums[i] + mid) - 
                       (begin(nums) + i) - 1;
            }
            if(cnt >= k) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};
/*
    0, 1, 2, 3, 4, 5
    0, 1, 1, 2, 2, 3
          <  >=   

    1, 2, 3, 4, 5
*/
