/*  計算連續數字的個數
 *
 *   1, 2, 3, 4, 3, 2, 5
 *   1  2  3  4  1  1  1      

 *   3, 2, 3, 2, 3, 2
 *   1, 1, 2, 1, 2, 1
 *
 *   當連續數字大於等於k 就輸出
 *
 *   time  : O(N)
 *   space : O(N)
 */

class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        if(k == 1) return nums;
        int cnt = 1;
        vector<int> rtn;
        for(int i = 1; i < nums.size(); ++i) {
            cnt = nums[i] == nums[i - 1] + 1 ? cnt + 1 : 1;
            if(i >= k - 1) rtn.push_back(cnt >= k ? nums[i] : -1);
        }
        return rtn;
    }
};
/*
*/
