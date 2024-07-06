/*
 *  參考下面的推導 當和前一個不一樣的時候就把ans + prev + 1;
 *                   和前面一樣就把prev = 1
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    long long countAlternatingSubarrays(vector<int>& nums) {
        long long ans{1};
        int prev{1};
        for(int i = 1; i < nums.size(); ++i) {
            prev = nums[i] ^ nums[i - 1] ? prev + 1 : 1;
            ans += prev;
        }
        return ans;
    }
};
/*
    1, 0, 1, 0
    1 -> 1
    1, 0 -> 2
    1, 0, 1 -> 3
    1, 0, 1, 0 -> 4

*/
