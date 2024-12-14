/*
    使用slinding window來找符合條件的subarray
    每找到一個subarray 由[left, right]組合而成的subarray都要加進ans

    使用map來記錄遇見的最大最小值 只要最大-最小 <= 2 即為符合的subarray

    time  : O(NlogN)
    space : O(N)
*/
class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        long long ans{};
        map<int, int> m; // value, count
        for(int left = 0, right = 0; right < nums.size(); ++right) {
            m[nums[right]]++;
            while((*m.rbegin()).first - (*m.begin()).first > 2) {
                if(--m[nums[left]] == 0)
                    m.erase(nums[left]);
                left++;
            }
            ans += right - left + 1;
        }
        return ans;
    }
};
/*
    5, 4, 2, 4
    | --> 1             minv = 5, maxv = 5
    |  | --> 2          minv = 4, maxv = 5
       |   |  --> 2     
       |     | --> 3

*/
